require 'pathname'

module BasicGenerator
  def init_generator(template_path="./", namespace=nil)
    @path = Pathname.new(template_path)
    @namespace = namespace

    if namespace
      @namespace_guard = namespace.upcase + "_" + @serialization_class_name.upcase
      @namespace_begin = "namespace #{namespace} {\n"
      @namespace_end = "}\n"
    else
      @namespace_guard = @serialization_class_name.upcase
      @namespace_begin = ""
      @namespace_end = ""
    end
  end

  def guard(macro_guard, text)
    if macro_guard.nil?
      return text
    end
    return "#include<libgeodecomp/config.h>\n#ifdef #{macro_guard}\n#{text}\n#endif\n"
  end

  def map_headers(headers, header_pattern, header_replacement)
    h = headers.map do |header|
      header_name = header
      if !header_replacement.nil?
        header_name = header.gsub(header_pattern, header_replacement)
      end
      "#include <#{header_name}>"
    end
    return h.join("\n")
  end

  # By default Boost/HPX Serialization will look in its own namespace
  # for suitable serialization functions. Those are defined here.
  def generate_namespace_link(klass, template_parameters)
    params1 = render_template_params1(template_parameters)
    params2 = render_template_params2(template_parameters)
    params1 = ", #{params1}" if params1.size > 0

    return <<EOF
template<class ARCHIVE#{params1}>
void serialize(ARCHIVE& archive, #{klass}#{params2}& object, const unsigned version)
{
    #{@serialization_class_name}::serialize(archive, object, version);
}
EOF
  end

  def generate_serialize_function(klass, members, parents, template_parameters)
    params1 = render_template_params1(template_parameters)
    params2 = render_template_params2(template_parameters)
    params1 = ", #{params1}" if params1.size > 0

    ret = <<EOF
    template<typename ARCHIVE#{params1}>
    inline
    static void serialize(ARCHIVE& archive, #{klass}#{params2}& object, const unsigned /*version*/)
    {
EOF

    parents.sort.each do |parent_type|
      ret += <<EOF
        archive & #{base_object_name}<#{parent_type} >(object);
EOF
    end

    members.keys.sort.each do |member|
      ret += <<EOF
        archive & object.#{member};
EOF
    end

    ret += <<EOF
    }
EOF

    return ret
  end

  def class_registrations(options)
    return ""
  end

  # the header generated by this function only contains the serialize() functions for Boost/HPX Serialize
  def generate_header(options)
    ret = File.read(@path + "template_serialization.h");
    ret.gsub!(/HEADERS/, map_headers(options.headers, options.header_pattern, options.header_replacement))
    ret.gsub!(/NAMESPACE_GUARD/, @namespace_guard)
    ret.gsub!(/NAMESPACE_BEGIN\n/, @namespace_begin)
    ret.gsub!(/NAMESPACE_END\n/, @namespace_end)
    ret.gsub!(/CLASS_REGISTRATIONS\n/, class_registrations(options))
    ret.gsub!(/SERIALIZATION_CLASS_NAME/, @serialization_class_name)
    ret.gsub!(/SERIALIZATION_NAMESPACE/, @serialization_namespace)

    serializations = options.topological_class_sortation.map do |klass|
      generate_serialize_function(klass,
                                  options.members[klass],
                                  options.resolved_parents[klass],
                                  options.template_params[klass])
    end
    ret.sub!(/.*SERIALIZATIION_DEFINITIONS/, serializations.join("\n"))

    serializations = options.topological_class_sortation.map do |klass|
      generate_namespace_link(klass, options.template_params[klass])
    end

    namespace = ""
    if !@namespace.nil?
      namespace = <<EOF
using namespace #{@namespace};
EOF
    end

    ret.sub!(/.*NAMESPACE_LINK/, ([ namespace ] + serializations).join("\n"))

    return guard(@macro_guard, ret)
  end

  def generate_source(options)
    ret = File.read(@path + "template_serialization.cpp");
    ret.gsub!(/MACROS\n/, class_registrations_source(options))

    return guard(@macro_guard, ret)
    return ret
  end

  def render_template_params1(template_parameters)
    params = template_parameters.map do |parameter|
      "#{parameter[:type]} #{parameter[:name]}"
    end

    return params.join(", ")
  end

  def render_template_params2(template_parameters)
    params = template_parameters.map { |parameter| parameter[:name] }
    params = params.join(", ")
    if (params.size > 0)
      params = "<#{params}>"
    end
  end
end
