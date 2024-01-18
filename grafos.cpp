#include <bits/stdc++.h>
using namespace std;
#define br "\n"
typedef long long ll;
#define pb push_back
#define pii pair<int, int>
#define pll pair<long long, long long>
#define forn(i, n) for(int i = 0; i < n; i++)

// BFS
const int maxn = 100;
vector<int> adj[maxn + 1];
int dis[maxn + 1];
int p[maxn + 1];
void bfs(int origin, int dest){
    dis[origin] = 0;
    queue<int>q;
    p[origin] = -1;
    q.push(origin);
    while(!q.empty()){
        int node = q.front();
        q.pop();
        for(int v : adj[node]){
            if(dis[v] == -1){
                dis[v] = dis[node] + 1;
                q.push(v);
                p[v] = node;
            }
        }
    }
}

// BFS em Grid
bool vis[maxn][maxn];
vector<int> grid[maxn];
int n, m;
bool inRange(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < m;
}
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int pieces = 0;
void bfs_grid(){
    forn(i, n){
        forn(j, m){
            if(!vis[i][j] && grid[i][j] == '#'){
                vis[i][j] = true;
                pieces++;
                queue<pair<int, int>> q;
                q.push({i, j});
                while(!q.empty()){
                    pair<int, int> p = q.front();
                    q.pop();
                    forn(i, 4){
                        int ax = p.first + dx[i]; int ay = p.second + dy[i];
                        if(inRange(ax, ay) && !vis[ax][ay] && grid[ax][ay] == '#'){
                            vis[ax][ay] = true;
                            q.push({ax, ay});
                        }
                    }
                }
            }
        }
    }
    return;
}


// DFS
vector<int> adj[maxn + 1];
int dis[maxn + 1];
int vis2[maxn + 1];
void dfs(int origin){
    vis2[origin] = true;
    for(int v : adj[origin]){
        if(!vis2[v]){       
            dis[v] = dis[origin] + 1;
            dfs(v);
        }      
    }
}

// DFS em Grid
int max_depth = 0;
void dfs_grid(int x, int y, set<pair<int, int>> q, int cur_depth){
    q.erase({x, y});
    cur_depth += grid[x][y];
    vis[x][y] = true;
    int cont = 0;
    forn(i, 4){
        int nx = x + dx[i]; int ny = y + dy[i];
        if(inRange(nx, ny) && !vis[nx][ny] && grid[nx][ny] != 0){
            dfs_grid(nx, ny, q, cur_depth);
        }
        else cont ++;
    }
    if(cont == 4 && !q.empty()){
        
        int x = (*q.begin()).first;
        int y = (*q.begin()).second;
        max_depth = max(cur_depth , max_depth);
        cur_depth = 0;
        dfs_grid(x, y, q, cur_depth);
    }
    max_depth = max(cur_depth , max_depth);
}

// Toposort
vector<int> adj[maxn + 1];
vector<int>indegree(maxn + 1, 0);
vector<int> topobfs(int n){
    vector<int>topo;
    priority_queue<int, vector<int>, std::greater<int>> pq;
    forn(i, n){
        if(indegree[i + 1] == 0) pq.push(i + 1);
    }
    while(!pq.empty()){
        int node = pq.top();
        pq.pop();
        topo.pb(node);
        for(int v : adj[node]){
            indegree[v]--;
            if(indegree[v] == 0)pq.push(v);
        }
    }
    return topo;
}

// Bicolorabilidade
for(int j = 1; j <= n; j++)
    {
        if(colour[j] == -1)
        {
            colour[j] = 0;
            dfs(j, colour, adj);
        }   
    }
void dfs(int u, int colour[], vector<int> adj[]){
    for(int v : adj[u]){
        if(colour[v] == -1){
            colour[v] = 1 - colour[u];
            dfs(v, colour,adj);
        }
    }
} 

// Dijkstra
void dijkstra(vector<pii>adj[], int n, int origin){
    priority_queue<pii, vector<pii>, greater<pii>>pq;
    int dis[n + 1];
    memset(dis, INT_MAX, sizeof(dis));
    dis[origin] = 0;
    pq.push({0, origin});

    while(!pq.empty()){
        int weight = pq.top().first;
        int v = pq.top().second;
        pq.pop();
        for(auto x : adj[v]){
            if(weight + x.second < dis[x.first]){
                dis[x.first] = weight + x.second;
                pq.push({dis[x.first], x.first});
            }
        } 
    }
    return;
}

// Floyd-Warshall

// STORE GRAPH IN ADJACENCY MATRIX
// IDENTIFIES NEGATIVE CYCLES
// PICKS UP THE INTERMEDIATE(VIA)(1ST FOR) AND PICKS UP A VERTEX(2ND FOR) AND UPDATES THE DISTANCE FOR EACH ONE OF THEM(3RD FOR)
void floyd_warshall(vector<vector<int>>distances, int n){
    forn(k, n){
        forn(i , n){
            forn(j , n){
                distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j]);
            }
        }
    }
    bool negcycle = false;
    forn(i , n){
        if(distances[i][i] < 0) negcycle = true;
    }
}
// DSU
class dsu{
    vector<int> root, size;
    public:
        dsu(int n){
            root.resize(n);
            size.resize(n, 1);
            forn(i, n){
                root[i] = i;
            }
        }
        int findRoot(int v){
            if(v == root[v]) return v;
            return root[v] = findRoot(root[v]);
        }

        void join(int u, int v){
            int pu = findRoot(u);
            int pv = findRoot(v);
            if(pu != pv){
                if(size[pu] < size[pv]){
                    root[pu] = pv;
                }
                else root[pv] = pu;
                size[pu] += size[pv];
                size[pv] = size[pu];
            }
        }
};

// MST - Kruskal(Com DSU)
int kruskal(vector<pair<int, pair<int, int>>>edges, int n){
    int sum = 0; int new_edges = 0;
    dsu dsu(n);
    sort(edges.begin(), edges.end());
    for(auto e : edges){
        int u = e.second.first;
        int v = e.second.second;
        int weight = e.first;
        if(dsu.findRoot(u) != dsu.findRoot(v)){
            dsu.join(u, v);
            sum += weight;
            new_edges++;
        }
    }
    return sum;
}


// MST - Prim(Com BFS)
int prim(int n, int origin, vector<pii>adj[]){
    int sum = 0;
    bool vis[n + 1];
    memset(vis, false, sizeof(vis));
    vector<pair<int, int>>mst(n - 1);
    priority_queue<pii, vector<pii>, greater<pii>>pq;
    pq.push({0, origin});
    while(!pq.empty()){
        int weight = pq.top().first;
        int v = pq.top().second;
        pq.pop();
        if(vis[v]) continue;
        vis[v] = true;
        sum += weight;
        for(auto u : adj[v]){
            // Considerando uma lista de adjacência de pares, guardando o nó e o peso, nessa ordem
            if(!vis[u.first]){
                pq.push({u.first, u.second});
            }
        }
    }
    return sum;
}

