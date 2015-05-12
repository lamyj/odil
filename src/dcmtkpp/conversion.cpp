/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/conversion.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Element.h"
#include "dcmtkpp/Tag.h"
#include "dcmtkpp/VR.h"

namespace dcmtkpp
{

DcmVR convert(VR vr)
{
    if(vr == VR::AE) { return EVR_AE; }
    else if(vr == VR::AS) { return EVR_AS; }
    else if(vr == VR::AT) { return EVR_AT; }
    else if(vr == VR::CS) { return EVR_CS; }
    else if(vr == VR::DA) { return EVR_DA; }
    else if(vr == VR::DS) { return EVR_DS; }
    else if(vr == VR::DT) { return EVR_DT; }
    else if(vr == VR::FL) { return EVR_FL; }
    else if(vr == VR::FD) { return EVR_FD; }
    else if(vr == VR::IS) { return EVR_IS; }
    else if(vr == VR::LO) { return EVR_LO; }
    else if(vr == VR::LT) { return EVR_LT; }
    else if(vr == VR::OB) { return EVR_OB; }
    else if(vr == VR::OF) { return EVR_OF; }
    else if(vr == VR::OW) { return EVR_OW; }
    else if(vr == VR::PN) { return EVR_PN; }
    else if(vr == VR::SH) { return EVR_SH; }
    else if(vr == VR::SL) { return EVR_SL; }
    else if(vr == VR::SQ) { return EVR_SQ; }
    else if(vr == VR::SS) { return EVR_SS; }
    else if(vr == VR::ST) { return EVR_ST; }
    else if(vr == VR::TM) { return EVR_TM; }
    else if(vr == VR::UI) { return EVR_UI; }
    else if(vr == VR::UL) { return EVR_UL; }
    else if(vr == VR::UN) { return EVR_UN; }
    else if(vr == VR::US) { return EVR_US; }
    else if(vr == VR::UT) { return EVR_UT; }
    else
    {
        throw Exception("Unknown VR");
    }
}

VR convert(DcmVR vr)
{
    DcmEVR const evr = vr.getValidEVR();
    if(evr == EVR_AE) { return VR::AE; }
    else if(evr == EVR_AS) { return VR::AS; }
    else if(evr == EVR_AT) { return VR::AT; }
    else if(evr == EVR_CS) { return VR::CS; }
    else if(evr == EVR_DA) { return VR::DA; }
    else if(evr == EVR_DS) { return VR::DS; }
    else if(evr == EVR_DT) { return VR::DT; }
    else if(evr == EVR_FL) { return VR::FL; }
    else if(evr == EVR_FD) { return VR::FD; }
    else if(evr == EVR_IS) { return VR::IS; }
    else if(evr == EVR_LO) { return VR::LO; }
    else if(evr == EVR_LT) { return VR::LT; }
    else if(evr == EVR_OB) { return VR::OB; }
    else if(evr == EVR_OF) { return VR::OF; }
    else if(evr == EVR_OW) { return VR::OW; }
    else if(evr == EVR_PN) { return VR::PN; }
    else if(evr == EVR_SH) { return VR::SH; }
    else if(evr == EVR_SL) { return VR::SL; }
    else if(evr == EVR_SQ) { return VR::SQ; }
    else if(evr == EVR_SS) { return VR::SS; }
    else if(evr == EVR_ST) { return VR::ST; }
    else if(evr == EVR_TM) { return VR::TM; }
    else if(evr == EVR_UI) { return VR::UI; }
    else if(evr == EVR_UL) { return VR::UL; }
    else if(evr == EVR_UN) { return VR::UN; }
    else if(evr == EVR_US) { return VR::US; }
    else if(evr == EVR_UT) { return VR::UT; }
    else
    {
        throw Exception("Unknown VR");
    }
}

DcmTagKey convert(Tag const & tag)
{
    return DcmTagKey(tag.group, tag.element);
}

Tag convert(DcmTagKey const & tag)
{
    return Tag(tag.getGroup(), tag.getElement());
}

DcmElement * convert(const Tag & tag, Element const & source)
{
    DcmTag const destination_tag(convert(tag), convert(source.vr));

    DcmElement * destination = NULL;
    if(source.vr == VR::AE)
    {
        destination = new DcmApplicationEntity(destination_tag);
        convert<Value::Strings>(source, destination, &Element::as_string);
    }
    else if (source.vr == VR::AS)
    {
        destination = new DcmAgeString(destination_tag);
        convert<Value::Strings>(source, destination, &Element::as_string);
    }
    // AT
    else if (source.vr == VR::CS)
    {
        destination = new DcmCodeString(destination_tag);
        convert<Value::Strings>(source, destination, &Element::as_string);
    }
    else if (source.vr == VR::DA)
    {
        destination = new DcmDate(destination_tag);
        convert<Value::Strings>(source, destination, &Element::as_string);
    }
    else if (source.vr == VR::DS)
    {
        destination = new DcmDecimalString(destination_tag);
        convert<Value::Reals>(source, destination, &Element::as_real);
    }
    else if (source.vr == VR::DT)
    {
        destination = new DcmDateTime(destination_tag);
        convert<Value::Strings>(source, destination, &Element::as_string);
    }
    else if (source.vr == VR::FD)
    {
        destination = new DcmFloatingPointDouble(destination_tag);
        convert<Value::Reals, Float64>(source, destination, &Element::as_real);
    }
    else if (source.vr == VR::FL)
    {
        destination = new DcmFloatingPointSingle(destination_tag);
        convert<Value::Reals, Float32>(source, destination, &Element::as_real);
    }
    else if (source.vr == VR::IS)
    {
        destination = new DcmIntegerString(destination_tag);
        convert<Value::Integers>(source, destination, &Element::as_int);
    }
    else if (source.vr == VR::LO)
    {
        destination = new DcmLongString(destination_tag);
        convert<Value::Strings>(source, destination, &Element::as_string);
    }
    else if (source.vr == VR::LT)
    {
        destination = new DcmLongText(destination_tag);
        convert<Value::Strings>(source, destination, &Element::as_string);
    }
    // OB
    // OF
    // OW
    else if (source.vr == VR::PN)
    {
        destination = new DcmPersonName(destination_tag);
        convert<Value::Strings>(source, destination, &Element::as_string);
    }
    else if (source.vr == VR::SH)
    {
        destination = new DcmShortString(destination_tag);
        convert<Value::Strings>(source, destination, &Element::as_string);
    }
    else if (source.vr == VR::SL)
    {
        destination = new DcmSignedLong(destination_tag);
        convert<Value::Integers, Sint32>(source, destination, &Element::as_int);
    }
    // SQ
    else if (source.vr == VR::SS)
    {
        destination = new DcmSignedShort(destination_tag);
        convert<Value::Integers, Sint16>(source, destination, &Element::as_int);
    }
    else if (source.vr == VR::ST)
    {
        destination = new DcmShortText(destination_tag);
        convert<Value::Strings>(source, destination, &Element::as_string);
    }
    else if (source.vr == VR::TM)
    {
        destination = new DcmTime(destination_tag);
        convert<Value::Strings>(source, destination, &Element::as_string);
    }
    else if (source.vr == VR::UI)
    {
        destination = new DcmUniqueIdentifier(destination_tag);
        convert<Value::Strings>(source, destination, &Element::as_string);
    }
    else if (source.vr == VR::UL)
    {
        destination = new DcmUnsignedLong(destination_tag);
        convert<Value::Integers, Uint32>(source, destination, &Element::as_int);
    }
    // UN
    else if (source.vr == VR::US)
    {
        destination = new DcmUnsignedShort(destination_tag);
        convert<Value::Integers, Uint16>(source, destination, &Element::as_int);
    }
    else if (source.vr == VR::UT)
    {
        destination = new DcmUnlimitedText(destination_tag);
        convert<Value::Strings>(source, destination, &Element::as_string);
    }
    else
    {
        throw Exception("Unknown VR");
    }

    return destination;
}

Element convert(DcmElement * source)
{
    Element destination;

    DcmEVR const source_vr = source->getTag().getVR().getValidEVR();

    if(source_vr == EVR_AE)
    {
        destination = Element(Value::Strings(), VR::AE);
        convert<std::string, Value::Strings>(source, destination, &Element::as_string);
    }
    else if(source_vr == EVR_AS)
    {
        destination = Element(Value::Strings(), VR::AS);
        convert<std::string, Value::Strings>(source, destination, &Element::as_string);
    }
    // AT
    else if(source_vr == EVR_CS)
    {
        destination = Element(Value::Strings(), VR::CS);
        convert<std::string, Value::Strings>(source, destination, &Element::as_string);
    }
    else if(source_vr == EVR_DA)
    {
        destination = Element(Value::Strings(), VR::DA);
        convert<std::string, Value::Strings>(source, destination, &Element::as_string);
    }
    else if(source_vr == EVR_DS)
    {
        destination = Element(Value::Reals(), VR::DS);
        convert<Float64, Value::Reals>(source, destination, &Element::as_real);
    }
    else if(source_vr == EVR_DT)
    {
        destination = Element(Value::Strings(), VR::DT);
        convert<std::string, Value::Strings>(source, destination, &Element::as_string);
    }
    else if(source_vr == EVR_FL)
    {
        destination = Element(Value::Reals(), VR::FL);
        convert<Float32, Value::Reals>(source, destination, &Element::as_real);
    }
    else if(source_vr == EVR_FD)
    {
        destination = Element(Value::Reals(), VR::FD);
        convert<Float64, Value::Reals>(source, destination, &Element::as_real);
    }
    else if(source_vr == EVR_IS)
    {
        destination = Element(Value::Integers(), VR::IS);
        convert<Sint32, Value::Integers>(source, destination, &Element::as_int);
    }
    else if(source_vr == EVR_LO)
    {
        destination = Element(Value::Strings(), VR::LO);
        convert<std::string, Value::Strings>(source, destination, &Element::as_string);
    }
    else if(source_vr == EVR_LT)
    {
        destination = Element(Value::Strings(), VR::LT);
        convert<std::string, Value::Strings>(source, destination, &Element::as_string);
    }
    // OB
    // OF
    // OW
    else if(source_vr == EVR_PN)
    {
        destination = Element(Value::Strings(), VR::PN);
        convert<std::string, Value::Strings>(source, destination, &Element::as_string);
    }
    else if(source_vr == EVR_SH)
    {
        destination = Element(Value::Strings(), VR::SH);
        convert<std::string, Value::Strings>(source, destination, &Element::as_string);
    }
    else if(source_vr == EVR_SL)
    {
        destination = Element(Value::Integers(), VR::SL);
        convert<Sint32, Value::Integers>(source, destination, &Element::as_int);
    }
    // SQ
    else if(source_vr == EVR_SS)
    {
        destination = Element(Value::Integers(), VR::SS);
        convert<Sint16, Value::Integers>(source, destination, &Element::as_int);
    }
    else if(source_vr == EVR_ST)
    {
        destination = Element(Value::Strings(), VR::ST);
        convert<std::string, Value::Strings>(source, destination, &Element::as_string);
    }
    else if(source_vr == EVR_TM)
    {
        destination = Element(Value::Strings(), VR::TM);
        convert<std::string, Value::Strings>(source, destination, &Element::as_string);
    }
    else if(source_vr == EVR_UI)
    {
        destination = Element(Value::Strings(), VR::UI);
        convert<std::string, Value::Strings>(source, destination, &Element::as_string);
    }
    else if(source_vr == EVR_UL)
    {
        destination = Element(Value::Integers(), VR::UL);
        convert<Uint32, Value::Integers>(source, destination, &Element::as_int);
    }
    // UN
    else if(source_vr == EVR_US)
    {
        destination = Element(Value::Integers(), VR::US);
        convert<Uint16, Value::Integers>(source, destination, &Element::as_int);
    }
    else if(source_vr == EVR_UT)
    {
        destination = Element(Value::Strings(), VR::UT);
        convert<std::string, Value::Strings>(source, destination, &Element::as_string);
    }
    else
    {
        throw Exception("Unknown VR");
    }

    return destination;
}

DcmDataset convert(DataSet const & source)
{
    DcmDataset destination;

    for(auto const & iterator: source)
    {
        auto const destination_element = convert(
            iterator.first, iterator.second);
        destination.insert(destination_element);
    }

    return destination;
}

DataSet convert(DcmDataset const & source)
{
    DataSet destination;

    for(unsigned long i=0; i<source.card(); ++i)
    {
        auto const source_element = const_cast<DcmDataset &>(source).getElement(i);

        auto const destination_tag = convert(source_element->getTag());
        auto const destination_element = convert(source_element);

        destination.add(destination_tag, destination_element);
    }
    return destination;
}

}
