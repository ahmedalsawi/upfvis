#include <vector>
#include <iostream>
#include <string>

class PowerNet;
class PowerPort;
class PowerDomain;

struct PowerState
{
    int state;
    int voltage;
};

class PowerPort
{
public:
    std::string name;

    PowerNet *loconn;
    PowerNet *highconn;

    std::string domain;

    PowerPort() {}
    ~PowerPort() {}
};

class PowerNet
{
public:
    std::string name;
    std::string domain;
    std::vector<std::string> ports;
};

class PowerDomain
{
public:
    std::string name;
    std::string scope;

    std::vector<std::string> elements;
    bool include_scope;

    friend std::ostream &operator<<(std::ostream &os, const PowerDomain &pd)
    {
        os << "Power Domain: Name: " << pd.name << std::endl;
        return os;
    }

    PowerDomain(std::string name) : name(name) {}
    ~PowerDomain() {}
};

class UPFEngine
{
    std::vector<PowerDomain> domains;
    std::string active_scope;

public:
    UPFEngine() = default;

    void run()
    {
        domains.push_back(PowerDomain("TOP"));
    }

    void dump_upf()
    {
        for (auto domain : this->domains)
        {
            std::cout << domain;
        }
    }
};

int main(int argc, char **argv)
{
    UPFEngine upf_instance;

    upf_instance.run();
    upf_instance.dump_upf();
}