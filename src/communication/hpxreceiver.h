#ifndef LIBGEODECOMP_COMMUNICATION_HPXRECEIVER_H
#define LIBGEODECOMP_COMMUNICATION_HPXRECEIVER_H

#include <hpx/lcos/local/receive_buffer.hpp>
#include <hpx/runtime/get_ptr.hpp>

namespace {
template<typename COMPONENT>
class hpx_plugin_exporter_factory;

template<typename COMPONENT>
class init_registry_factory_static;

template<typename T>
class hpx_plugin_exporter_registry;

}

namespace LibGeoDecomp {

template <typename CARGO, typename BUFFER=hpx::lcos::local::receive_buffer<CARGO> >
class HPXReceiver : public hpx::components::simple_component_base<HPXReceiver<CARGO> >
{
public:
    typedef CARGO Cargo;
    typedef BUFFER Buffer;

    static hpx::future<boost::shared_ptr<HPXReceiver> > make(const std::string& name)
    {
        hpx::id_type id = hpx::new_<HPXReceiver>(hpx::find_here()).get();
        hpx::register_with_basename(name, id, 0).get();
        return hpx::get_ptr<HPXReceiver>(id);
    }

    static hpx::future<hpx::id_type> find(const std::string& name)
    {
        std::vector<hpx::future<hpx::id_type> > ids = hpx::find_all_from_basename(name, 1);
        if (ids.size() != 1) {
            throw std::logic_error("Unexpected amount of PatchProviders found in AGAS, expected exactly 1");
        }

        return std::move(ids[0]);
    }

    virtual ~HPXReceiver()
    {}

    void receive(std::size_t step, Cargo&& val)
    {
        buffer.store_received(step, std::move(val));
    }
    HPX_DEFINE_COMPONENT_ACTION(HPXReceiver, receive, receiveAction);

    hpx::future<Cargo> get(std::size_t step)
    {
        return buffer.receive(step);
    }

    virtual hpx_plugin_exporter_factory<HPXReceiver> hpx_plugin_exporter_factory_registration()
    {
        return hpx_plugin_exporter_factory<HPXReceiver>::instance;
    }

    virtual init_registry_factory_static<HPXReceiver> hpx_init_registry_factory_static_registration()
    {
        return init_registry_factory_static<HPXReceiver>::instance;
    }

    virtual hpx_plugin_exporter_registry<HPXReceiver> hpx_plugin_exporter_registry_registration()
    {
        return hpx_plugin_exporter_registry<HPXReceiver>::instance;
    }

private:
    Buffer buffer;
};

}
#endif
