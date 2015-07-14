load 'basicgenerator.rb'

# Here we generate the C++ code that will in turn create the typemaps
# for Boost Serialization.
class BoostGenerator
  include BasicGenerator

  def initialize(template_path="./", namespace=nil, macro_guard_boost=nil)
    init_generator(template_path, namespace)
    @macro_guard = macro_guard_boost
  end

  def base_object_name
    "boost::serialization::base_object"
  end

  # wraps the code generation for multiple typemaps.
  def generate_forest(resolved_classes, resolved_parents, template_parameters, class_sortation, headers, header_pattern=nil, header_replacement=nil)
    return [generate_header(class_sortation, resolved_classes, resolved_parents, template_parameters, headers, header_pattern, header_replacement)]
  end
end
