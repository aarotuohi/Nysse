// Datastructures.hh
//
// Student name:
// Student email:
// Student number:

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <map>
#include <set>

// Types for IDs
using TownID = std::string;
using Name = std::string;

// Return values for cases where required thing was not found
TownID const NO_TOWNID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

struct Town {
    Name name;
    Coord coord;
    int distance;
    int tax;
    Name road;
    std::string vassal_town = NO_NAME;
    bool visited;
};
// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: 0(n)
    // Short rationale for estimate: lineaarisesti laskee map tietorakenteen koon
    unsigned int town_count();

    // Estimate of performance: 0(n)
    // Short rationale for estimate: Poistaa kaikki tiedot kerrallaan
    void clear_all();

    // Estimate of performance: O(log n)
    // Short rationale for estimate: lisaa halutut tiedot mappiin tehokkuudella O(log n)
    //
    bool add_town(TownID id, Name const& name, Coord coord, int tax);

    // Estimate of performance: O(log n)
    // Short rationale for estimate: Mapista avaimen hakemisen tehokkuus
    Name get_town_name(TownID id);

    // Estimate of performance: O(log n)
    // Short rationale for estimate: mapista hakemisen tehokkuus on O(log n)
    Coord get_town_coordinates(TownID id);

    // Estimate of performance: O(log n)
    // Short rationale for estimate: mapista hakemisen tehokkuus on O(log n)
    int get_town_tax(TownID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: mapista järjestysnumeron perusteella haun tehokkuus on O(n)
    std::vector<TownID> all_towns();

    // Estimate of performance: O(log n)
    // Short rationale for estimate: Mapista hakuavaimella hakeminen käy lineaarisesti mapin läpi ja
    // jos avain löytyy lisää se nimen vektoriin.
    std::vector<TownID> find_towns(Name const& name);

    // Estimate of performance: O(n)
    // Short rationale for estimate: etsii id ja vaihtaa nimen eli kay kerran läpi rakenteen
    bool change_town_name(TownID id, Name const& newname);

    // Estimate of performance:O(n log(n))
    // Short rationale for estimate: Käy loopilla läpi ja sorttaa lisättyyn vektoriin järjestyksessä
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance:O(n log(n)
    // Short rationale for estimate: sorttaa ja käy loopilla läpi vektorin arvot
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance:O(n)
    // Short rationale for estimate: käy läpi tietorakenteen ja palauttaa towns_distance_increasing
    // järjestyksen ensimmäisen arvon
    TownID min_distance();

    // Estimate of performance:O(n)
    // Short rationale for estimate: käy läpi tietorakenteen ja palauttaa towns_distance_increasing
    // järjestyksen viimeisen arvon
    TownID max_distance();

    // Estimate of performance: O(log n)
    // Short rationale for estimate: Kulkee mapin läpi lineaarisesti ja jos masterid tai vassalid id
    // ei löydy lisää yhteyden.
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: looppaa mapin läpi n kertaa ja lisaa
    // halutun id:n arvot vektoriin
    std::vector<TownID> get_town_vassals(TownID id);

    // Estimate of performance: O(log n)
    // Short rationale for estimate: datan kasvaessa lineaarisesti myös fukntion teho kärsii sitä myötä.
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory phase 1 operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: Find etsii halutun kapungin id ja jos loytaa poistaan sen.
    bool remove_town(TownID id);

    // Estimate of performance:O(nlog(n)+2n)
    // Short rationale for estimate: kaksi for looppia vievät tehokkuuden 2n ja loopin sorttauksen tehokkuus
    // on O(nlog(n))
    std::vector<TownID> towns_nearest(Coord coord);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    int total_net_tax(TownID id);


    // Phase 2 operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: Poistaa kaikki tiet vectorista yksi kerrallaan lineaarisesti
    void clear_roads();

    // Estimate of performance: O(n)
    // Short rationale for estimate: käy jokaisen tien läpi vekotrista for loopin avulla ja
    // puskee ne vektori pariin
    std::vector<std::pair<TownID, TownID>> all_roads();

    // Estimate of performance: O(n)
    // Short rationale for estimate: lisää tien vekori pariin,jos id löytyy tietorakenteesta map.
    bool add_road(TownID town1, TownID town2);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: for loop O(n) käy tietorakenteen ja sorttaa ne järjestykseen
    std::vector<TownID> get_roads_from(TownID id);

    // Estimate of performance:O(nlog(n)+ n)
    // Short rationale for estimate: jos kaupunki loytyy tie sekä lahtopaikasta että tulopaikasta lisataan
    // kaupunki vektoriin. Käyttää apunaan apufunktiota Depth_First_Search,jossa lisätään kaupungin id map
    // tietorakenteeseen ja kaupungista lähtevät tiet. Käydään looppien avulla läpi O(n) ja jos kaupungissa on
    // jo käyty.
    std::vector<TownID> any_route(TownID fromid, TownID toid);

    // Non-compulsory phase 2 operations

    // Estimate of performance: O(n log(n))
    // Short rationale for estimate: Find etsii halutun kapungin id vektorista lineaarisesti ja jos loytaa poistaan sen.
    // käy läpi parin molemmat arvot
    bool remove_road(TownID town1, TownID town2);

    // Estimate of performance:O (nlog(n) + n)
    // Short rationale for estimate: kutsuu any_route funktiota, joten sama tehokkuus kun any_routessa
    std::vector<TownID> least_towns_route(TownID fromid, TownID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> road_cycle_route(TownID startid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> shortest_route(TownID fromid, TownID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    Distance trim_road_network();

private:

   bool Depth_First_Search(TownID fromid,TownID toid);

   std::map<TownID, Town> Towns_info;

   std::vector<std::pair<TownID,TownID>> road_info;

   std::pair<TownID,TownID> route_pair;

   std::map<std::string, std::vector<TownID>> graph;

   std::vector<TownID> path_to_city;


    // Add stuff needed for your class implementation here

};

#endif // DATASTRUCTURES_HH
