//
// Generated file, do not edit! Created by opp_msgtool 6.0 from msg.msg.
//

#ifndef __MSG_M_H
#define __MSG_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class Msg;
/**
 * Class generated from <tt>msg.msg:19</tt> by opp_msgtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * packet Msg
 * {
 *     \@customize(true);  // see the generated C++ header for more info
 *     int sequenceNumber;
 *     string payload;
 *     string trailer;
 *     string frameType;
 *     int ackNackNumber;
 * }
 * </pre>
 *
 * Msg_Base is only useful if it gets subclassed, and Msg is derived from it.
 * The minimum code to be written for Msg is the following:
 *
 * <pre>
 * class Msg : public Msg_Base
 * {
 *   private:
 *     void copy(const Msg& other) { ... }

 *   public:
 *     Msg(const char *name=nullptr, short kind=0) : Msg_Base(name,kind) {}
 *     Msg(const Msg& other) : Msg_Base(other) {copy(other);}
 *     Msg& operator=(const Msg& other) {if (this==&other) return *this; Msg_Base::operator=(other); copy(other); return *this;}
 *     virtual Msg *dup() const override {return new Msg(*this);}
 *     // ADD CODE HERE to redefine and implement pure virtual functions from Msg_Base
 * };
 * </pre>
 *
 * The following should go into a .cc (.cpp) file:
 *
 * <pre>
 * Register_Class(Msg)
 * </pre>
 */
class Msg_Base : public ::omnetpp::cPacket
{
  
  private:
    void copy(const Msg_Base& other);

  protected:
    

  public:
   int sequenceNumber = 0;
    omnetpp::opp_string payload;
    omnetpp::opp_string trailer;
    omnetpp::opp_string frameType;
    int ackNackNumber = 0;
  bool operator==(const Msg_Base&) = delete;
    // make constructors protected to avoid instantiation
    Msg_Base(const char *name=nullptr, short kind=0);
    Msg_Base(const Msg_Base& other);
    // make assignment operator protected to force the user override it
    Msg_Base& operator=(const Msg_Base& other);
    virtual ~Msg_Base();
    virtual Msg_Base *dup() const override {return new Msg_Base(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getSequenceNumber() const;
    virtual void setSequenceNumber(int sequenceNumber);

    virtual const char * getPayload() const;
    virtual void setPayload(const char * payload);

    virtual const char * getTrailer() const;
    virtual void setTrailer(const char * trailer);

    virtual const char * getFrameType() const;
    virtual void setFrameType(const char * frameType);

    virtual int getAckNackNumber() const;
    virtual void setAckNackNumber(int ackNackNumber);
};


namespace omnetpp {

template<> inline Msg_Base *fromAnyPtr(any_ptr ptr) { return check_and_cast<Msg_Base*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __MSG_M_H
