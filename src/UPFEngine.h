#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <tcl.h>

class PowerNet;
class PowerPort;
class PowerDomain;

struct PowerState
{
    int state;
    int voltage;
};

enum class PPORT_DIR
{
    IN,
    OUT,
    INOUT
};

class PowerNet
{

public:
    std::string name;
    std::string domain; // provided in command

    // Deduced from create_supply_net if -domain is used, it creates object in the same logical hierarchy as domain. if not, it uses active scope.
    std::string scope;

    // resolved ports names to port objects
    std::vector<PowerPort *> ports;

    friend std::ostream &operator<<(std::ostream &os, const PowerNet &pd)
    {
        os << "Power Net: Name: " << pd.name << std::endl;
        return os;
    }
};

class PowerPort
{

public:
    std::string name;
    std::string domain; // provided in command

    PPORT_DIR direction = PPORT_DIR::IN; // default "in"

    // deduced from create_supply_port... if -domain is used, it creates object in the same logical hierarchy as domain. if not, it uses active scope.
    std::string scope;

    // resolve Low and High connection
    PowerNet *LowConn;
    PowerNet *HighConn;

    PowerDomain *domain_pd;

    friend std::ostream &operator<<(std::ostream &os, const PowerPort &pd)
    {
        os << "Power Port: Name: " << pd.name << std::endl;
        return os;
    }
};

class PowerDomain
{

public:
    std::string name;
    std::string scope;

    std::vector<std::string> elements;
    std::vector<std::string> exclude_elements;
    bool include_scope;

    // resolved nets and ports
    std::vector<PowerNet *> nets;
    std::vector<PowerPort *> ports;

    friend std::ostream &operator<<(std::ostream &os, const PowerDomain &pd)
    {
        os << "Power Domain: Name: " << pd.name << std::endl;
        os << "Power Domain: elements: " << std::endl;
        for (auto el : pd.elements)
        {
            os << "\t" << el << std::endl;
        }
        return os;
    }
};

class UPFEngine
{
public:
    std::vector<PowerDomain> domains;
    std::vector<PowerPort> ports;
    std::vector<PowerNet> nets;

    std::string active_scope;
    std::string root; // TODO Pare root name on CLI

    UPFEngine() = default;

    void run()
    {
        PowerDomain domain;
        domain.elements.push_back("/dd/dd");
        domains.push_back(domain);

        PowerPort port;
        std::string scope;
        port.name = "port1";
        port.domain = "domain1";
        for (auto domain : domains)
        {
            if (domain.name == port.domain)
            {
                scope = domain.scope;
                domain.ports.push_back(&port);
                break;
            }
        }
        port.scope = scope;
        ports.push_back(port);
    }

    void dump_upf()
    {
        for (auto domain : this->domains)
        {
            std::cout << domain;
        }
        for (auto port : this->ports)
        {
            std::cout << port;
        }
        for (auto net : this->nets)
        {
            std::cout << net;
        }
    }
};