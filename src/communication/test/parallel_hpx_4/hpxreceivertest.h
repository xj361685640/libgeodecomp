#include <cxxtest/TestSuite.h>
#include <hpx/hpx.hpp>
#include <hpx/runtime/serialization/serialize_buffer.hpp>
#include <libgeodecomp/communication/hpxreceiver.h>
#include <libgeodecomp/misc/stringops.h>

// fixme: find unified macro for this, or even better: define template magic for this, akin to serialization macros
// typedef LibGeoDecomp::HPXReceiver<std::vector<int> > ReceiverType1;
typedef LibGeoDecomp::HPXReceiver<std::vector<int> > ReceiverType1;
typedef LibGeoDecomp::HPXReceiver<hpx::serialization::serialize_buffer<char> > ReceiverType2;
typedef LibGeoDecomp::HPXReceiver<double> ReceiverType3;

// int ficken1;

// typedef hpx::components::simple_component<ReceiverType1> ReceiverType1Component;
// HPX_REGISTER_COMPONENT(ReceiverType1Component, ReceiverType1Component );

// int ficken2;

// typedef ReceiverType1::receiveAction ReceiverType1ComponentReceiveActionReceiveAction;
// HPX_REGISTER_ACTION(ReceiverType1ComponentReceiveActionReceiveAction);

// int ficken3 = "";

int ficken1;

// typedef hpx::components::simple_component<ReceiverType1> ReceiverType1Component;

extern "C" __attribute__((visibility ("default")))
std::map<std::string, boost::any> * hpx_exported_plugins_list_hpx_factory();

namespace {

template<typename COMPONENT>
class hpx_plugin_exporter_factory;

template<>
class hpx_plugin_exporter_factory<ReceiverType1>
{
public:
    hpx_plugin_exporter_factory()
    {
        static hpx::util::plugin::concrete_factory< hpx::components::component_factory_base, hpx::components::component_factory<hpx::components::simple_component<ReceiverType1>> > cf;
        hpx::util::plugin::abstract_factory<hpx::components::component_factory_base>* w = &cf;

        std::string actname(typeid(hpx::components::simple_component<ReceiverType1>).name());
        boost::algorithm::to_lower(actname);
        hpx_exported_plugins_list_hpx_factory()->insert( std::make_pair(actname, w));
    }

    static hpx_plugin_exporter_factory instance;
    static void ping()
    {
        std::cout << &instance;
    }

};

hpx_plugin_exporter_factory<ReceiverType1> hpx_plugin_exporter_factory<ReceiverType1>::instance;

}

extern "C" __attribute__((visibility ("default")))

std::map<std::string, boost::any>* hpx_exported_plugins_list_hpx_factory();

namespace {

template<typename COMPONENT>
class init_registry_factory_static;

template<>
class init_registry_factory_static<ReceiverType1>
{
public:
    init_registry_factory_static<ReceiverType1>()
    {
        hpx::components::static_factory_load_data_type data = { typeid(hpx::components::simple_component<ReceiverType1>).name(), hpx_exported_plugins_list_hpx_factory };
        hpx::components::init_registry_factory(data);
    }

    static init_registry_factory_static<ReceiverType1> instance;

    static void ping()
    {
        std::cout << &instance;
    }
};

init_registry_factory_static<ReceiverType1> init_registry_factory_static<ReceiverType1>::instance;

}

namespace hpx {
namespace components {

template <> struct unique_component_name<hpx::components::component_factory<hpx::components::simple_component<ReceiverType1>> >
{
    typedef char const* type; static type call (void)
    {
        return typeid(hpx::components::simple_component<ReceiverType1>).name();
    }
};
}
}

template struct hpx::components::component_factory<hpx::components::simple_component<ReceiverType1>>;
// typedef hpx::components::component_registry<ReceiverType1Component, ::hpx::components::factory_check> ReceiverType1Component_component_registry_type;

extern "C" __attribute__((visibility ("default")))
std::map<std::string, boost::any> * hpx_exported_plugins_list_hpx_registry();

namespace {
struct hpx_plugin_exporter_registry_hpx_ReceiverType1Component
{
    hpx_plugin_exporter_registry_hpx_ReceiverType1Component()
    {
        static hpx::util::plugin::concrete_factory< hpx::components::component_registry_base, hpx::components::component_registry<hpx::components::simple_component<ReceiverType1>, ::hpx::components::factory_check> > cf;
        hpx::util::plugin::abstract_factory<hpx::components::component_registry_base>* w = &cf;
        // std::string actname("ReceiverType1Component");
        std::string actname(typeid(hpx::components::simple_component<ReceiverType1>).name());
        boost::algorithm::to_lower(actname);
        hpx_exported_plugins_list_hpx_registry()->insert( std::make_pair(actname, w));
    }
} hpx_plugin_exporter_instance_registry_hpx_ReceiverType1Component;
}

namespace hpx {
namespace components {

template <>
struct unique_component_name<hpx::components::component_registry<hpx::components::simple_component<ReceiverType1>, ::hpx::components::factory_check> >
{
    typedef char const* type;
    static type call (void)
    {
        return typeid(hpx::components::simple_component<ReceiverType1>).name();
    }
};

}
}

template struct hpx::components::component_registry< hpx::components::simple_component<ReceiverType1>, ::hpx::components::factory_check>;

namespace hpx {
namespace traits {

template <>
__attribute__((visibility("default")))
components::component_type component_type_database<hpx::components::simple_component<ReceiverType1>::wrapped_type>::get()
{
    return value;
}

template <>
__attribute__((visibility("default")))
void component_type_database<hpx::components::simple_component<ReceiverType1>::wrapped_type>::set( components::component_type t)
{
    value = t;
}

}};

int ficken2;

// typedef ReceiverType1::receiveAction ReceiverType1ComponentReceiveActionReceiveAction;

namespace hpx {
namespace actions {
namespace detail {

template<>
__attribute__((visibility("default")))
char const* get_action_name<ReceiverType1::receiveAction// ReceiverType1ComponentReceiveActionReceiveAction
                            >()
{
    return typeid(ReceiverType1::receiveAction).name();
}

}}};

int ficken3;


typedef hpx::components::simple_component<ReceiverType2> ReceiverType2Component;
HPX_REGISTER_COMPONENT(ReceiverType2Component, ReceiverType2Component );
typedef ReceiverType2::receiveAction ReceiverType2ComponentReceiveActionReceiveAction;
HPX_REGISTER_ACTION(ReceiverType2ComponentReceiveActionReceiveAction);

typedef hpx::components::simple_component<ReceiverType3> ReceiverType3Component;
HPX_REGISTER_COMPONENT(ReceiverType3Component, ReceiverType3Component );
typedef ReceiverType3::receiveAction ReceiverType3ComponentReceiveActionReceiveAction;
HPX_REGISTER_ACTION(ReceiverType3ComponentReceiveActionReceiveAction);

using namespace LibGeoDecomp;

namespace LibGeoDecomp {

class HPXReceiverTest : public CxxTest::TestSuite
{
public:
    void mySetUp(std::string basename)
    {
        rank = hpx::get_locality_id();
        size = hpx::find_all_localities().size();

        leftNeighbor  = (rank - 1 + size) % size;
        rightNeighbor = (rank + 1       ) % size;

        name      = basename + "/" + StringOps::itoa(rank);
        leftName  = basename + "/" + StringOps::itoa(leftNeighbor);
        rightName = basename + "/" + StringOps::itoa(rightNeighbor);
    }

    void testBasic()
    {
        mySetUp("HPXReceiverTest::testBasic");
        boost::shared_ptr<ReceiverType1> receiver = ReceiverType1::make(name).get();

        hpx::id_type leftID  = ReceiverType1::find(leftName ).get();
        hpx::id_type rightID = ReceiverType1::find(rightName).get();

        std::vector<int> sendVec;
        sendVec << rank;
        hpx::apply(ReceiverType1::receiveAction(), leftID,  10, sendVec);
        hpx::apply(ReceiverType1::receiveAction(), rightID, 11, sendVec);

        std::vector<int> fromLeft  = receiver->get(11).get();
        std::vector<int> fromRight = receiver->get(10).get();

        TS_ASSERT_EQUALS(1, fromLeft.size());
        TS_ASSERT_EQUALS(1, fromRight.size());
        TS_ASSERT_EQUALS(leftNeighbor,  fromLeft[0]);
        TS_ASSERT_EQUALS(rightNeighbor, fromRight[0]);

        hpx::unregister_with_basename(name, 0);
    }

    void testWithSerializationBuffer()
    {
        mySetUp("HPXReceiverTest::testWithSerializationBuffer");

        std::vector<char> sendToLeft( rank + 10, char(leftNeighbor));
        std::vector<char> sendToRight(rank + 10, char(rightNeighbor));
        hpx::serialization::serialize_buffer<char> sendLeftBuffer( &sendToLeft[0],  sendToLeft.size());
        hpx::serialization::serialize_buffer<char> sendRightBuffer(&sendToRight[0], sendToRight.size());

        boost::shared_ptr<ReceiverType2> receiver = ReceiverType2::make(name).get();

        hpx::id_type leftID  = ReceiverType2::find(leftName ).get();
        hpx::id_type rightID = ReceiverType2::find(rightName).get();

        hpx::apply(ReceiverType2::receiveAction(), leftID,  20, sendLeftBuffer);
        hpx::apply(ReceiverType2::receiveAction(), rightID, 21, sendRightBuffer);

        hpx::serialization::serialize_buffer<char> fromLeft  = receiver->get(21).get();
        hpx::serialization::serialize_buffer<char> fromRight = receiver->get(20).get();

        TS_ASSERT_EQUALS(rank, std::size_t(fromLeft[0]));
        TS_ASSERT_EQUALS(rank, std::size_t(fromRight[0]));
        TS_ASSERT_EQUALS(10 + leftNeighbor,  fromLeft.size());
        TS_ASSERT_EQUALS(10 + rightNeighbor, fromRight.size());

        hpx::unregister_with_basename(name, 0);
    }

    void testWithDouble()
    {
        mySetUp("HPXReceiverTest::testWithDouble");

        double sendToLeft  = rank + 10.123;
        double sendToRight = rank + 10.234;

        boost::shared_ptr<ReceiverType3> receiver = ReceiverType3::make(name).get();

        hpx::id_type leftID  = ReceiverType3::find(leftName ).get();
        hpx::id_type rightID = ReceiverType3::find(rightName).get();

        hpx::apply(ReceiverType3::receiveAction(), leftID,  30, sendToLeft);
        hpx::apply(ReceiverType3::receiveAction(), rightID, 31, sendToRight);

        double fromLeft  = receiver->get(31).get();
        double fromRight = receiver->get(30).get();

        TS_ASSERT_EQUALS(10.234 + leftNeighbor,  fromLeft);
        TS_ASSERT_EQUALS(10.123 + rightNeighbor, fromRight);

        hpx::unregister_with_basename(name, 0);
    }

private:
    std::size_t rank;
    std::size_t size;
    std::size_t leftNeighbor;
    std::size_t rightNeighbor;

    std::string name;
    std::string leftName;
    std::string rightName;
};

}