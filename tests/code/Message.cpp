#define BOOST_TEST_MODULE Message
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Message.h"

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::Message const message;

    // Command Set might not be empty (Command Group Length, Data Set Type)
    BOOST_CHECK_EQUAL(
        message.get_data_set(), static_cast<DcmDataset const *>(NULL));
}

BOOST_AUTO_TEST_CASE(Constructor)
{
    DcmDataset command_set;
    dcmtkpp::ElementAccessor<EVR_US>::set(
        command_set, DCM_CommandField, DIMSE_C_ECHO_RQ);

    DcmDataset data_set;

    dcmtkpp::Message const message(command_set, &data_set);

    BOOST_CHECK_EQUAL(
        dcmtkpp::ElementAccessor<EVR_US>::get(
            message.get_command_set(), DCM_CommandField),
        DIMSE_C_ECHO_RQ);

    BOOST_CHECK(
        message.get_data_set() != NULL &&
        const_cast<DcmDataset *>(message.get_data_set())->isEmpty());

    BOOST_CHECK_EQUAL(message.get_command_field(), DIMSE_C_ECHO_RQ);
}

BOOST_AUTO_TEST_CASE(DeleteDataSet)
{
    DcmDataset command_set;
    DcmDataset * data_set = new DcmDataset();

    dcmtkpp::Message message(command_set, data_set);

    BOOST_CHECK(
        message.get_data_set() != NULL &&
        const_cast<DcmDataset *>(message.get_data_set())->isEmpty());

    message.delete_data_set();

    BOOST_CHECK_EQUAL(
        message.get_data_set(), static_cast<DcmDataset const*>(NULL));
}
