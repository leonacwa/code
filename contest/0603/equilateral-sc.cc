// Solution to "Equilateral Dominoes" problem
// 2010 Stanford Local Programming Contest
// Sonny Chan, October 1, 2010

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

// using a 3-axis coordinate system for this problem
struct coord {
    int a, b, c;
    coord(int aa = 0, int bb = 0, int cc = 0) : a(aa), b(bb), c(cc) { }
    int parity() const { return (a+b+c) & 1; }
    coord next(int i) const {
        if (i == 0)      return parity() ? coord(a-1, b, c) : coord(a+1, b, c);
        else if (i == 1) return parity() ? coord(a, b-1, c) : coord(a, b+1, c);
        else             return parity() ? coord(a, b, c-1) : coord(a, b, c+1);
    }
};

bool operator<(const coord &x, const coord &y)
{
    if (x.a == y.a) {
        if (x.b == y.b) return x.c < y.c;
        return x.b < y.b;
    }
    return x.a < y.a;
}

bool operator!=(const coord &x, const coord &y)
{
    return x.a != y.a || x.b != y.b || x.c != y.c;
}

// structure for a domino
struct domino {
    int pips[2];
    bool used;
    domino(int a, int b) : used(false) { pips[0] = a; pips[1] = b; }
};

ostream &operator<<(ostream &stream, const domino &d)
{
    stream << '<' << d.pips[0] << '|' << d.pips[1] << '>';
    return stream;
}

// test if a cell can be filled with a certain value
bool canplace(const coord &target, int n, map<coord, int> &tiled)
{
    if (tiled.count(target) > 0 && tiled[target] != n) return false;
    for (int i = 0; i < 3; ++i) {
        if (tiled.count(target.next(i)) == 0) continue;
        if (tiled[target.next(i)] != n) return false;
    }
    return true;                  
}

// score the placement of a half-domino
int score(const coord &target, int n, map<coord, int> &tiled)
{
    int s = 0;
    for (int i = 0; i < 3; ++i) {
        if (tiled.count(target.next(i)) == 0) continue;
        if (tiled[target.next(i)] == n) ++s;
    }
    return s;          
}

// recursive tiling search function
int search(vector<domino> &d, map<coord, int> &tiled, list<coord> &fringe, int points)
{
    int best = points;
    
    // for every unused domino
    for (vector<domino>::iterator di = d.begin(); di != d.end(); ++di)
    {
        if (di->used) continue;
    
        // look for a spot on the fringe to place the domino
        for (list<coord>::iterator fi = fringe.begin(); fi != fringe.end(); ++fi)
        {
            // check each end in turn
            for (int e = 0; e < 2; ++e)
            {
                if (!canplace(*fi, di->pips[e], tiled)) continue;
                int a = di->pips[e];
                int b = di->pips[(e+1)%2];

                // if end can be placed in the target spot, try different orientations in turn
                int nd = tiled.empty() ? 1 : 3;
                for (int dir = 0; dir < nd; ++dir)
                {
                    coord g = fi->next(dir);
                    if (!canplace(g, b, tiled)) continue;
                    
                    // if domino can be placed in this orientation, 
                    // update the score and then do so
                    int bonus = score(*fi, a, tiled) + score(g, b, tiled);
                    tiled[*fi] = a;
                    tiled[g] = b;
                    di->used = true;
        
                    // update the fringe
                    int fc = 0;
                    for (int i = 0; i < 3; ++i) {
                        coord h = fi->next(i);
                        if (h != g && tiled.count(h) == 0) {
                            ++fc;
                            fringe.push_back(h);
                        }
                        h = g.next(i);
                        if (h != *fi && tiled.count(h) == 0) {
                            ++fc;
                            fringe.push_back(h);
                        }
                    }
                    
                    // recurse, counting score
                    best = max(best, search(d, tiled, fringe, points + bonus));
                    
                    // remove the domino and clean up fringe
                    tiled.erase(*fi);
                    tiled.erase(g);
                    di->used = false;
                    for (int i = 0; i < fc; ++i)
                        fringe.pop_back();
                }
            }
        }
    }
    
    return best;
}


int main()
{
    int n;
    while (cin >> n)
    {
        if (n == 0) break;
        
        // read the dominoes
        vector<domino> d;
        for (int i = 0; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            d.push_back(domino(a, b));
        }
        
        // set up variables and then do recursive search
        map<coord, int> tiled;
        list<coord> fringe;
        fringe.push_back(coord(0,0,0));
        
        cout << search(d, tiled, fringe, 0) << endl;
    }
    
    return 0;
}

