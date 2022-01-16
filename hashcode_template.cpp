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
#define _shuffle(_x) random_shuffle(_x.begin(), _x.end())
#define r_sort(_x)   sort(_x.rbegin(), _x.rend())
#define MAX_VAL_OF(_x) std::numeric_limits<decltype(_x)>::max()
#define v_int vector<int>

int sum(vector<int>& v) { int total = 0; fi(v.size()) total += v[i]; return total; }
float mean(vector<int>& v) { return sum(v) / v.size(); }
float standardDeviation(vector<int>& v) { float mu = mean(v); float s = 0; fi(v.size()) s += pow(v[i] - mu, 2); return sqrt(s / v.size()); }
void reverseStringIntMap(map<string, int>& input_map, map<int, string>& output_map) { for (map<string, int>::iterator it = input_map.begin(); it != input_map.end(); it++) output_map.insert({it->second, it->first}); }
int stringIdInMap(map<string, int> &map_, string &str_) { map<string, int>::iterator it = map_.find(str_); if (it == map_.end()) { map_.insert({str_, map_.size()}); } else { return it->second; } return map_.size() - 1; }


// Data element
struct Element {
    v_int tags;
    int orientation;
    int id;
};


class Problem {
    public:
        // Write solution to file
        void writeFile(ofstream &file)
        {
            file << solution.size() << "\n";
            fi(solution.size())
            {
                fj(solution[i].size())
                    file << solution[i][j].id << " ";
                file << "\n";
            }
        }

        // Read file to data structures
        void readFile(fstream &file)
        {
            int num_images; file >> num_images;
            fi(num_images)
            {
                Element e; string orientation, tag; int num_tags;

                file >> orientation >> num_tags;
                if (orientation == "H") { e.orientation = 0; } else { e.orientation = 1; }
                e.id = i;
                fj(num_tags)
                {
                    file >> tag;
                    e.tags.push_back(stringIdInMap(tags_to_id, tag));
                }
                data.push_back(e);
            }
        }

        // Create solution vector
        void solve()
        {
            // Comparator example: [](auto& i, auto& j) { return i > j; }
            fi(data.size())
                solution.push_back({data[i]});
            _shuffle(solution);
        }
    private:
        // Add data structures
        map<string, int> tags_to_id;
        vector<Element> data;
        vector<vector<Element>> solution;
};


int main()
{
    // Change input and output file names
    vector<string> in_file_names = {
        "input_files/a.txt",
        "input_files/b.txt",
        "input_files/c.txt",
        "input_files/d.txt",
        "input_files/e.txt",
        "input_files/f.txt",
    };
    vector<string> out_file_names = {
        "a_solution.txt",
        "b_solution.txt",
        "c_solution.txt",
        "d_solution.txt",
        "e_solution.txt",
        "f_solution.txt",
    };
    fi(in_file_names.size())
    {
        Problem p;

        // 1. Read
        fstream in_file; in_file.open(in_file_names[i], ios::in);
        p.readFile(in_file);
        in_file.close();

        // 2. Solve
        p.solve();

        // 3. Write
        ofstream out_file; out_file.open(out_file_names[i]);
        p.writeFile(out_file);
        out_file.close();
    }
}
