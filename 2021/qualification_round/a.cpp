#include <vector>
#include <map>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
#include <functional>
#include <iterator>
#include <random>
#include <list>
#include <queue>
#include <cstdlib>
#include <string>
#include <memory.h>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <bitset>
#include <fstream>
#include <deque>
#include <cmath>
#include <numeric>
#include <stack>
#include <stdarg.h>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
#define fi(n) for (int i = 0; i < int (n); i++)
#define fj(n) for (int j = 0; j < int (n); j++)
#define fk(n) for (int k = 0; k < int (n); k++)
#define f1(_n) for (auto&i1 : _n)
#define f2(_n) for (auto&i2 : _n)
#define f3(_n) for (auto&i3 : _n)
#define all(n) n.begin(), n.end()
#define break(_x)    {_x;break;}
#define continue(_x) {_x;continue;}
#define _sort(_x)    sort(_x.begin(), _x.end())
#define r_sort(_x)   sort(_x.rbegin(), _x.rend())
#define MAX_VAL_OF(_x) std::numeric_limits<decltype(_x)>::max()
#define v_int vector<int>

tuple<
    map<string, int>,
    map<int, v_int>,
    map<int, pair<v_int, v_int>>,
    vector<v_int>,
    map<int, int>,
    map<int, int>> readFile(string file_name)
{
    fstream file;
    file.open(file_name, ios::in);
    int duration, num_intersections, num_streets, num_cars, bonus;
    file >> duration >> num_intersections >> num_streets >> num_cars >> bonus;
    map<string, int> street_name_map;
    map<int, v_int> streets;
    map<int, pair<v_int, v_int>> intersections;  // id, (input_it, output_it)
    vector<v_int> car_paths;

    map<int, int> street_count;
    map<int, int> start_street_count;

    while(num_streets--)
    {
        int start_i, end_i, street_time;
        string street_name;
        file >> start_i >> end_i >> street_name >> street_time;
        map<string, int>::iterator street_name_it = street_name_map.find(street_name);
        // street
        int street_id;
        if (street_name_it == street_name_map.end())
        {
            street_id = street_name_map.size();
            street_name_map.insert({street_name, street_id});
            streets.insert({street_id, {start_i, end_i, street_time}});
        }
        else
            street_id = street_name_it->second;
        // intersections
        map<int, pair<v_int, v_int>>::iterator inter_it = intersections.find(start_i);
        if (inter_it != intersections.end())
            inter_it->second.second.push_back(street_id);
        else
            intersections.insert({start_i, {{}, {street_id}}});
        inter_it = intersections.find(end_i);
        if (inter_it != intersections.end())
            inter_it->second.first.push_back(street_id);
        else
            intersections.insert({end_i, {{street_id}, {}}});
    }
    for (map<int, v_int>::iterator it = streets.begin(); it != streets.end(); it++)
    {
        street_count.insert({it->first, 0});
        start_street_count.insert({it->first, 0});
    }
    while(num_cars--)
    {
        int num_car_paths;
        file >> num_car_paths;
        v_int path_ids;
        int total_drive_time = 0;
        while(num_car_paths--)
        {
            string street_name;
            file >> street_name;
            map<string, int>::iterator street_name_it = street_name_map.find(street_name);
            int street_id = street_name_it->second;
            path_ids.push_back(street_id);
            map<int, v_int>::iterator street_it = streets.find(street_id);
            total_drive_time += street_it->second[2];
        }
        if (duration*0.7 < total_drive_time) continue;
        car_paths.push_back(path_ids);
        start_street_count.find(path_ids[0])->second++;
        fi(path_ids.size()) street_count.find(path_ids[i])->second++;
    }
    file.close();
    tuple<
    map<string, int>,
    map<int, v_int>,
    map<int, pair<v_int, v_int>>,
    vector<v_int>,
    map<int, int>,
    map<int, int>> a = {
        street_name_map,
        streets,
        intersections,
        car_paths,
        street_count,
        start_street_count,};
    return a;
}

void writeFile(vector<pair<int, vector<pair<string, int>>>> a, string file_name)
{
    ofstream file;
    file.open(file_name);
    file << a.size() << "\n";
    fi(a.size())
    {
        file << a[i].first << "\n";
        file << a[i].second.size() << "\n";
        fj(a[i].second.size())
            file << a[i].second[j].first << " " << a[i].second[j].second << "\n";
    }
    file.close();
}

map<int, string> reverseStreetMap(map<string, int> street_name_map)
{
    map<int, string> reversed_street_name_map;
    for (map<string, int>::iterator it = street_name_map.begin();
    it != street_name_map.end(); it++)
        reversed_street_name_map.insert({it->second, it->first});
    return reversed_street_name_map;
}

void solve(string in_file, string out_file)
{
    tuple<
    map<string, int>, // street_name_map
    map<int, v_int>, // streets
    map<int, pair<v_int, v_int>>, // intersections
    vector<v_int>, // car_paths
    map<int, int>, // street_count
    map<int, int> // start_street_count
    > a = readFile(in_file);

    map<string, int> street_name_id = get<0>(a);
    map<int, v_int> streets = get<1>(a);
    map<int, pair<v_int, v_int>> intersections = get<2>(a);
    vector<v_int> car_paths = get<3>(a);
    map<int, int> street_count = get<4>(a);
    map<int, int> start_street_count = get<5>(a);

    map<int, string> street_id_name = reverseStreetMap(street_name_id);

    vector<pair<int, vector<pair<string, int>>>> b;
    for (map<int, pair<v_int, v_int>>::iterator it = intersections.begin();
        it != intersections.end(); it++)
    {
        int inter_id = it->first;
        vector<pair<string, int>> incoming_streets_seconds;
        vector<pair<int, int>> start_cars_per_street;
        int total_weights = 0;
        int min_count = 0;
        int max_count = 0;
        fj(it->second.first.size())
        {
            int incoming_street_id = it->second.first[j];
            int count = street_count.find(incoming_street_id)->second;
            int incoming_street_start_cars = start_street_count.find(incoming_street_id)->second;
            start_cars_per_street.push_back({incoming_street_id, incoming_street_start_cars});
            if (j==0)
            {
                min_count = count;
                max_count = count;
            }
            if (count < min_count) min_count = count;
            if (count > max_count) max_count = count;
            total_weights += count;
        }
        min_count = max(1, min_count);
        map<int, string>::iterator street_name;
        sort(all(start_cars_per_street), [](auto& i, auto& j) { return i.second > j.second; });

        fj(start_cars_per_street.size())
        {
            int incoming_street_id = start_cars_per_street[j].first;
            int count = street_count.find(incoming_street_id)->second;
            street_name = street_id_name.find(incoming_street_id);
            int time = sqrt((2*count + 5*start_cars_per_street[j].second) / 5 / min_count);
            if (time == 0) time = 1;
            if (count > 0) incoming_streets_seconds.push_back({street_name->second, time});
        }
        if (incoming_streets_seconds.size() == 0)
            incoming_streets_seconds.push_back({street_name->second, 1});
        b.push_back({inter_id, incoming_streets_seconds});
    }
    writeFile(b, out_file);
}


int main()
{
   vector<string> in_files = {
      "input_files/a.txt",
      "input_files/b.txt",
      "input_files/c.txt",
      "input_files/d.txt",
      "input_files/e.txt",
      "input_files/f.txt",
   };
   vector<string> out_files = {
      "a_solution.txt",
      "b_solution.txt",
      "c_solution.txt",
      "d_solution.txt",
      "e_solution.txt",
      "f_solution.txt",
   };
   fi(in_files.size())
      solve(in_files[i], out_files[i]);
}