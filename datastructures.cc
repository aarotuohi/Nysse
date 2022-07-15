// Datastructures.cc
//
// Student name:
// Student email:
// Student number:

#include "datastructures.hh"

#include <random>
#include <map>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{

    // Write any cleanup you need here
}
// Funktio palauttaa mapissa olevien kaupunkien lukumäärään
// ja palauttaa sen
unsigned int Datastructures::town_count()
{


    // Tehokkuudeltaan funktio on 0(n) sillä sen tehokkuus pysyy aina samana
    return Towns_info.size();

}
// Funktio poistaa tietorakenteesta kaikki arvot
void Datastructures::clear_all()
{
    // Replace the line below with your implementation
    Towns_info.clear();
    road_info.clear();
}
// Funktio ottaa parametreikseen kaupungin id, nimen, koordinaatit ja verotuksen määrän
// Lisää annnetut parametrit tietorakenteeseen map insertin avulla
bool Datastructures::add_town(TownID id, const Name &name, Coord coord, int tax)
{
    // find aikavaatimus mapille tehokkuudella on 0(log n)
    if(Towns_info.find(id) == Towns_info.end()){
        Town new_town;
        new_town.name = name;
        new_town.coord = coord;
        new_town.tax = tax;
        // insert aikavaatimus on 0(log n)
        Towns_info.insert({id,new_town});
        return true;

    }
    else{
        return false;
    }

}
// Funktio palauttaa mapista halutun kaupungin nimen kayttamalla id avaimena
Name Datastructures::get_town_name(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )

    //const std::string town_name = Towns.at(id).name;
    // at opertaation tehokkuus on 0(log n)
    if(Towns_info.find(id) != Towns_info.end()){
        return Towns_info.at(id).name;

    }
    else{
        return NO_NAME;
    }

    //throw NotImplemented("get_town_name()");
}
// Funktio palauttaa mapista halutun kaupungin koordinaatit kayttamalla id avaimena
Coord Datastructures::get_town_coordinates(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    //const struct Coord coords = Towns.at(id).coord;

    // at operaation tehokkuus on 0(log n)
    if(Towns_info.find(id) != Towns_info.end()){
        return Towns_info.at(id).coord;

    }
    else{
        return NO_COORD;
    }

}
// Funktio palauttaa mapista halutun kaupungin verot kayttamalla id avaimena
int Datastructures::get_town_tax(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    //const int towns_taxes = Towns.at(id).tax;

    // at operaation tehokkuus on 0(log n)
    if(Towns_info.find(id) != Towns_info.end()){
        return Towns_info.at(id).tax;

    }
    else{
        return NO_VALUE;
    }

}
// fukntio lisää kaikki kaupungit loopin avulla vektoriin ja palauttaa vektorin arvot
std::vector<TownID> Datastructures::all_towns()
{
    // Replace the line below with your implementation
    std::vector<TownID> towns;

    for(std::map<TownID, Town>::iterator it = Towns_info.begin();it != Towns_info.end();it++){
        //push_back tehokkuus 0(1)
        towns.push_back(it->first);

    }
    return towns;
}

std::vector<TownID> Datastructures::find_towns(const Name & name )
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    std::vector<TownID> find_towns;
    // iterating through map and if in struct name is same as wanted name pushes it back to vector
    // find_towns
    for(std::map<TownID, Town>::iterator it = Towns_info.begin();it != Towns_info.end();it++){
        if(it->second.name == name){
            find_towns.push_back(it->first);
        }
    }
    return find_towns;
}
// Funktio vaihtaa kaupungin nimen (name) uudeksi (newname)
bool Datastructures::change_town_name(TownID id, const Name & newname)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )

    // if given ID is not in datastructure retrun false
    // if ID is in map changes its name to given newname
    if(Towns_info.find(id) == Towns_info.end()){
        return false;
    }
    else{
        Towns_info.at(id).name = newname;
        return true;
    }

}
bool Comparison(const std::pair<TownID,Town> &a,const std::pair<TownID, Town> &b)
{
       return a.first < b.first;
}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    // Replace the line below with your implementation

    // iterating through the map and pushes back ID of the town. then sort it in alphabetical order using
    // compareFunction

    std::vector<TownID> distance;
    std::vector<std::pair<TownID, Town>> vertailu;
    // Kopioidaan mapin arvot vektoriin, jotta sorttaaminen onnistuisi helpommin
    std::copy(Towns_info.begin(), Towns_info.end(),std::back_inserter(vertailu));
    // vektorin sorttaus tehokkuudella O(n log n)
    std::sort(vertailu.begin(), vertailu.end(),Comparison);
    for(const auto& comp : vertailu){
        //std::sort(comp.first.begin(), comp.first.end(), Comparison);
        distance.push_back(comp.first);

    }
    return distance;

}

// apufunktio jossa vertaillaan Coord struction x:n arvoja ja palautetaan arvot pienemmästä
// suurimpaan
bool myComparison(const std::pair<TownID,Town> &a,const std::pair<TownID, Town> &b)
{
       return a.second.coord.x < b.second.coord.x;
}

// Funktio järjestää kaupungit järjestyksessä x koordinaattien peruteella pienemmästä
// suurimpaan
std::vector<TownID> Datastructures::towns_distance_increasing()
{
    // Replace the line below with your implementation

    std::vector<TownID> distance;
    std::vector<std::pair<TownID, Town>> vertailu;
    // Kopioidaan mapin arvot vektoriin, jotta sorttaaminen onnistuisi helpommin
    std::copy(Towns_info.begin(), Towns_info.end(),std::back_inserter(vertailu));
    // vektorin sorttaus tehokkuudella O(n log n)
    std::sort(vertailu.begin(), vertailu.end(),myComparison);

    for(const auto& comp : vertailu){
        distance.push_back(comp.first);

    }
    return distance;
}

TownID Datastructures::min_distance()
{
    // Replace the line below with your implementation


    if(Towns_info.size() == 0){
        return NO_TOWNID;
    }
    else{
        return towns_distance_increasing().front();
    }

}

TownID Datastructures::max_distance()
{
    // Replace the line below with your implementation


    if(Towns_info.size() == 0){
        return NO_TOWNID;
    }
    else{

        return towns_distance_increasing().back();
    }

}

bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{

    if(Towns_info.find(vassalid) == Towns_info.end() or Towns_info.find(masterid) == Towns_info.end()){
        return false;

    }
    else{
        Towns_info.at(vassalid).vassal_town = masterid;
        return true;
    }
}

std::vector<TownID> Datastructures::get_town_vassals(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    std::vector<TownID> vassals;
    if(Towns_info.find(id) != Towns_info.end()){
        for(std::map<TownID, Town>::iterator it = Towns_info.begin();it != Towns_info.end();it++){
            if(it->second.vassal_town == id){
                vassals.push_back(it->first);

            }
        }
        return vassals;

    }
    else{
        vassals.push_back(NO_TOWNID);
        return vassals;
    }
}

std::vector<TownID> Datastructures::taxer_path(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    std::vector<TownID> taxes;
    if(Towns_info.find(id) != Towns_info.end()){
        taxes.push_back(id);

        while(Towns_info.at(id).vassal_town != NO_NAME){

            taxes.push_back(Towns_info.at(id).vassal_town);
            Towns_info.at(id).vassal_town = Towns_info.at(Towns_info.at(id).vassal_town).vassal_town;

        }
        return taxes;

    }
    else{
        taxes.push_back(NO_TOWNID);
        return taxes;

    }

}

bool Datastructures::remove_town(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )

    // erase is O(1) notation
    if(Towns_info.find(id) != Towns_info.end()){

        Towns_info.erase(id);
        return true;
    }
    else{
        return false;
    }
}
bool myDistanceComparison(const std::pair<TownID,int> &a,const std::pair<TownID, int> &b)
{
       return a.second < b.second;
}
std::vector<TownID> Datastructures::towns_nearest(Coord coord)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("towns_nearest()");
    std::vector<TownID> coordinates;
    std::vector<std::pair<TownID,int>> distance;
    for(std::map<TownID, Town>::iterator it = Towns_info.begin();it != Towns_info.end();it++){

        int distance_calc = sqrt(((it->second.coord.x*it->second.coord.x)
                        -2*it->second.coord.x*coord.x+(coord.x*coord.x))+
                       (it->second.coord.y*it->second.coord.y)
                       -2*it->second.coord.y*coord.y+(coord.y*coord.y));
        distance.push_back({it->first,distance_calc});
    }
    //sorttaa etäisyyden perusteella hyodyntaen apufunktio myDistanceComparison
    std::sort(distance.begin(),distance.end(),myDistanceComparison);

    for(std::vector<std::pair<TownID, int>>::iterator it_ = distance.begin();it_ != distance.end();it_++){
        coordinates.push_back(it_->first);
    }
    return coordinates;

}

std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    //throw NotImplemented("longest_vassal_path()");
    std::vector<TownID> vassals;
    if(Towns_info.find(id) != Towns_info.end()){
        for(std::map<TownID, Town>::iterator it = Towns_info.begin();it != Towns_info.end();it++){
            if(it->second.vassal_town == id){
                vassals.push_back(it->first);

            }
        }
        return vassals;

    }
    else{
        vassals.push_back(NO_TOWNID);
        return vassals;
    }
}

int Datastructures::total_net_tax(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("longest_vassal_path()");
    int taxes = Towns_info.at(id).tax;
    return taxes;


}

//
// Phase 2 operations
//

// Poistaa kaikki tiet
void Datastructures::clear_roads()
{
    // Replace the line below with your implementation
    road_info.clear();
}

// Tulostaa kaikki vektoriin lisätyt tiet
std::vector<std::pair<TownID, TownID>> Datastructures::all_roads()
{
    // Replace the line below with your implementation

    std::vector<std::pair<TownID, TownID>> all_roads;
    for(std::vector<std::pair<TownID, TownID>>::iterator it = road_info.begin();it != road_info.end();it++){
        all_roads.push_back({it->first,it->second});

    }

    return all_roads;
}

// Lisää tietorakenteeseen tiet ja tarkistaa suuruusjärjestyksen lisäyksessä
bool Datastructures::add_road(TownID town1, TownID town2)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )


    if(Towns_info.find(town1) != Towns_info.end() or Towns_info.find(town2) != Towns_info.end()){
        if(town1 < town2){ //pienempi id ensin
            route_pair.first = town1;
            route_pair.second = town2;

        }else{
            route_pair.first = town2;
            route_pair.second = town1;

        }

        road_info.push_back(route_pair);
        return true;

    }else{
        return false;

    }




}

// etsii alkuperäisestä tietorakenteesta löytyyko parametri id ja jos löytyy sorttaa ja käy
// loopilla läpi vektorin. jos ensimmäinen tai toinen arvo parista on sama kuin id
//lisää vektoriin ja ei löydy lisää vektoriin (NO_TOWNID)
std::vector<TownID> Datastructures::get_roads_from(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    std::vector<TownID> roads_from_town;

    if(Towns_info.find(id) != Towns_info.end()){
        std::sort(road_info.begin(),road_info.end());
        for(std::vector<std::pair<TownID, TownID>>::iterator it = road_info.begin();it != road_info.end();it++){
                if(it->first == id){

                    roads_from_town.push_back(it->second);

                }
                else if(it->second == id){
                    roads_from_town.push_back(it->first);
                }
        }
    }
    else{
        roads_from_town.push_back(NO_TOWNID);
        return roads_from_town;

    }

    return roads_from_town;
}

// Syvyys ensin haku jossa otetaan map tietorakenne avuksi.

bool Datastructures::Depth_First_Search(TownID fromid,TownID toid){
    //jos on käyty lisätään mappiin

    for(std::map<TownID,Town>::iterator it_ = Towns_info.begin(); it_ != Towns_info.end();it_++){
        Towns_info[fromid].visited = true;

        graph.insert({it_->first, get_roads_from(it_->first)});

    }


    if(fromid == toid){

        for(std::map<TownID,Town>::iterator it = Towns_info.begin(); it != Towns_info.end();it++){
            Towns_info[it->first].visited = false;

        }

        path_to_city.push_back(fromid);
        return true;

    }else{
        for(const TownID& i : graph[fromid]){

            if(Towns_info[i].visited == false and Depth_First_Search(i,toid) == true){
                        path_to_city.push_back(fromid);
                        return true;
                    }
                    continue;
            }
    }

    return false;

}

// Etsitään reitti kahden kaupungin välillä ja palautetaan se. Jos ei löydy palauttaa
// NO_TOWNID
std::vector<TownID> Datastructures::any_route(TownID fromid, TownID toid)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )


    if(!path_to_city.empty()){
        path_to_city.clear();
    }

    if(Depth_First_Search(fromid,toid) == true){

        std::reverse(path_to_city.begin(),path_to_city.end());
        return path_to_city;


    }else{

        path_to_city.push_back(NO_TOWNID);
    }
    return path_to_city;


}

// Poistetaan tiet
bool Datastructures::remove_road(TownID town1, TownID town2)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    //road_info.begin(),road_info.end(),
    if(Towns_info.find(town1) != Towns_info.end() or Towns_info.find(town2) != Towns_info.end()){
        std::vector < std::pair<TownID,TownID>>::iterator iter= road_info.begin();
            while(iter != road_info.end())
            {
                if(iter->first==town1 and iter->second==town2){
                    iter = road_info.erase(iter);
                }
                else if(iter->first==town2 and iter->second==town1){
                    iter = road_info.erase(iter);
                }
                else{
                    ++iter;
                }

            }

    }
    else{
        return false;

    }
    return true;


}

// Etsitään lyhin reitti kapunkien välillä
std::vector<TownID> Datastructures::least_towns_route(TownID fromid, TownID toid)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )

    return any_route(fromid,toid);
}

std::vector<TownID> Datastructures::road_cycle_route(TownID /*startid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("road_cycle_route()");
}

std::vector<TownID> Datastructures::shortest_route(TownID /*fromid*/, TownID /*toid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("shortest_route()");
}

Distance Datastructures::trim_road_network()
{
    // Replace the line below with your implementation
    throw NotImplemented("shortest_route()");

}
