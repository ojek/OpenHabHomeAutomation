#ifndef ABSTRACT_ITEM
#define ABSTRACT_ITEM

#include <string.h>
#include <map>

class IItem
{
protected:
    void setProps(String _name, String _loopPriority)
    {
        name = _name;
        loopPriority = _loopPriority;
    }
public:

    virtual void setup(String _name, String _loopPriority)=0;
    virtual void loop()=0;
    virtual String command(String command)=0;

    std::map<String, String> pubChannels; //in
    std::map<String, String> subChannels; //out

    String name;
    String loopPriority;
};

#endif  //ABSTRACT_ITEM