//
// Generated file, do not edit! Created by opp_msgtool 6.0 from msg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "msg_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Msg_Base::Msg_Base(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

Msg_Base::Msg_Base(const Msg_Base& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

Msg_Base::~Msg_Base()
{
}

Msg_Base& Msg_Base::operator=(const Msg_Base& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Msg_Base::copy(const Msg_Base& other)
{
    this->sequenceNumber = other.sequenceNumber;
    this->payload = other.payload;
    this->trailer = other.trailer;
    this->frameType = other.frameType;
    this->ackNackNumber = other.ackNackNumber;
}

void Msg_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->payload);
    doParsimPacking(b,this->trailer);
    doParsimPacking(b,this->frameType);
    doParsimPacking(b,this->ackNackNumber);
}

void Msg_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->payload);
    doParsimUnpacking(b,this->trailer);
    doParsimUnpacking(b,this->frameType);
    doParsimUnpacking(b,this->ackNackNumber);
}

int Msg_Base::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void Msg_Base::setSequenceNumber(int sequenceNumber)
{
    this->sequenceNumber = sequenceNumber;
}

const char * Msg_Base::getPayload() const
{
    return this->payload.c_str();
}

void Msg_Base::setPayload(const char * payload)
{
    this->payload = payload;
}

const char * Msg_Base::getTrailer() const
{
    return this->trailer.c_str();
}

void Msg_Base::setTrailer(const char * trailer)
{
    this->trailer = trailer;
}

const char * Msg_Base::getFrameType() const
{
    return this->frameType.c_str();
}

void Msg_Base::setFrameType(const char * frameType)
{
    this->frameType = frameType;
}

int Msg_Base::getAckNackNumber() const
{
    return this->ackNackNumber;
}

void Msg_Base::setAckNackNumber(int ackNackNumber)
{
    this->ackNackNumber = ackNackNumber;
}

class MsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sequenceNumber,
        FIELD_payload,
        FIELD_trailer,
        FIELD_frameType,
        FIELD_ackNackNumber,
    };
  public:
    MsgDescriptor();
    virtual ~MsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(MsgDescriptor)

MsgDescriptor::MsgDescriptor() : omnetpp::cClassDescriptor("Msg", "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

MsgDescriptor::~MsgDescriptor()
{
    delete[] propertyNames;
}

bool MsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Msg_Base *>(obj)!=nullptr;
}

const char **MsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *MsgDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "true";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int MsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int MsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        FD_ISEDITABLE,    // FIELD_payload
        FD_ISEDITABLE,    // FIELD_trailer
        FD_ISEDITABLE,    // FIELD_frameType
        FD_ISEDITABLE,    // FIELD_ackNackNumber
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *MsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sequenceNumber",
        "payload",
        "trailer",
        "frameType",
        "ackNackNumber",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int MsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "payload") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "trailer") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "frameType") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "ackNackNumber") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *MsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sequenceNumber
        "string",    // FIELD_payload
        "string",    // FIELD_trailer
        "string",    // FIELD_frameType
        "int",    // FIELD_ackNackNumber
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **MsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *MsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int MsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Msg_Base *pp = omnetpp::fromAnyPtr<Msg_Base>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void MsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Msg_Base *pp = omnetpp::fromAnyPtr<Msg_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Msg_Base'", field);
    }
}

const char *MsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Msg_Base *pp = omnetpp::fromAnyPtr<Msg_Base>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string MsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Msg_Base *pp = omnetpp::fromAnyPtr<Msg_Base>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: return long2string(pp->getSequenceNumber());
        case FIELD_payload: return oppstring2string(pp->getPayload());
        case FIELD_trailer: return oppstring2string(pp->getTrailer());
        case FIELD_frameType: return oppstring2string(pp->getFrameType());
        case FIELD_ackNackNumber: return long2string(pp->getAckNackNumber());
        default: return "";
    }
}

void MsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Msg_Base *pp = omnetpp::fromAnyPtr<Msg_Base>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2long(value)); break;
        case FIELD_payload: pp->setPayload((value)); break;
        case FIELD_trailer: pp->setTrailer((value)); break;
        case FIELD_frameType: pp->setFrameType((value)); break;
        case FIELD_ackNackNumber: pp->setAckNackNumber(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Msg_Base'", field);
    }
}

omnetpp::cValue MsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Msg_Base *pp = omnetpp::fromAnyPtr<Msg_Base>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: return pp->getSequenceNumber();
        case FIELD_payload: return pp->getPayload();
        case FIELD_trailer: return pp->getTrailer();
        case FIELD_frameType: return pp->getFrameType();
        case FIELD_ackNackNumber: return pp->getAckNackNumber();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Msg_Base' as cValue -- field index out of range?", field);
    }
}

void MsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Msg_Base *pp = omnetpp::fromAnyPtr<Msg_Base>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_payload: pp->setPayload(value.stringValue()); break;
        case FIELD_trailer: pp->setTrailer(value.stringValue()); break;
        case FIELD_frameType: pp->setFrameType(value.stringValue()); break;
        case FIELD_ackNackNumber: pp->setAckNackNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Msg_Base'", field);
    }
}

const char *MsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr MsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Msg_Base *pp = omnetpp::fromAnyPtr<Msg_Base>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void MsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Msg_Base *pp = omnetpp::fromAnyPtr<Msg_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Msg_Base'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

