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
#include <filesystem>

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

int argmax(v_int v) { v_int::iterator max = max_element(all(v)); return distance(v.begin(), max); }
bool elementIn(int e, v_int v) { f1(v) { if(e == i1) return true; } return false; }
float mean(vector<int>& v) { return sum(v) / v.size(); }
int sum(vector<int>& v) { int total = 0; fi(v.size()) total += v[i]; return total; }
void reverseStringIntMap(map<string, int>& input_map, map<int, string>& output_map) { for (map<string, int>::iterator it = input_map.begin(); it != input_map.end(); it++) output_map.insert({it->second, it->first}); }
int randint(int start, int end) { std::random_device rd; std::mt19937 gen(rd()); std::uniform_int_distribution<> distr(start, end); return distr(gen); }
v_int nDifferentRandints(int n, int start, int end) { v_int v1; int d = end - start; if (n > d) n = d+1; fi(d+1) v1.push_back(i + start); _shuffle(v1); v_int v2; fi(n) v2.push_back(v1[i]); _sort(v2); return v2; }
int stringIdInMap(map<string, int> &map_, string &str_) { map<string, int>::iterator it = map_.find(str_); if (it == map_.end()) { map_.insert({str_, map_.size()}); } else { return it->second; } return map_.size() - 1; }
float standardDeviation(vector<int>& v) { float mu = mean(v); float s = 0; fi(v.size()) s += pow(v[i] - mu, 2); return sqrt(s / v.size()); }


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
            file << solution_.size() << "\n";
            fi(solution_.size())
            {
                fj(solution_[i].size())
                    file << solution_[i][j].id << " ";
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
                    e.tags.push_back(stringIdInMap(tags_to_id_, tag));
                }
                data_.push_back(e);
            }
            reverseStringIntMap(tags_to_id_, id_to_tag_);
        }

        // Create solution vector
        void solve()
        {
            // Comparator example: [](auto& i, auto& j) { return i > j; }
            fi(data_.size())
                solution_.push_back({data_[i]});
            _shuffle(solution_);
        }

    private:
        // Add data structures
        map<string, int> tags_to_id_;
        map<int, string> id_to_tag_;
        vector<Element> data_;
        vector<vector<Element>> solution_;
};


int main()
{
    // Change input file directory
    string input_directory_path = "input_data";

    // Read and sort input file names
    set<string> input_file_paths;
    f1(filesystem::directory_iterator(input_directory_path))
        input_file_paths.insert(i1.path());

    f1(input_file_paths)
    {
        // In and out paths
        string in_path = i1;
        string in_basename = in_path.substr(in_path.find_last_of("/\\") + 1);
        stringstream ss;
        ss << in_basename[0] << "_solution.txt";
        string out_path = ss.str();

        cout << "\n" << in_basename << endl;
        Problem p;

        // 1. Read
        fstream in_file; in_file.open(in_path, ios::in);
        p.readFile(in_file);
        in_file.close();

        // 2. Solve
        p.solve();

        // 3. Write
        ofstream out_file; out_file.open(out_path);
        p.writeFile(out_file);
        out_file.close();
    }
    return 1;
}
