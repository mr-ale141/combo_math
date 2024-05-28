#include "PairFinder.h"
#include <set>
#include <sstream>
#include <queue>

PairFinder::PairFinder(std::istream& in)
{
    std::set<int> uSet;
    std::vector<int> uVector;
    std::set<int> vSet;
    std::vector<int> vVector;
	std::string str;

	while (std::getline(in, str))
	{
		std::stringstream ss(str);
		int u{}, v{};
		if (ss >> u >> v)
		{
            uSet.insert(u);
            uVector.push_back(u);
            vSet.insert(v);
            vVector.push_back(v);
		}
		else
		{
			throw std::invalid_argument("Error in input graph");
		}
	}

    m_uSize = static_cast<int>(uSet.size());
	m_vSize = static_cast<int>(vSet.size());
	m_adj = std::vector<std::list<int>>(m_uSize + 1);
    
    for (size_t i = 0; i < uVector.size(); ++i)
        AddEdge(uVector[i], vVector[i]);
}

void PairFinder::AddEdge(int u, int v)
{
	m_adj[u].push_back(v);
}

bool PairFinder::Bfs()
{
    std::queue<int> q;

    for (int u = 1; u <= m_uSize; u++)
    {
        if (m_pairU[u] == NIL) 
        {
            m_dist[u] = 0;
            q.push(u);
        }
        else 
            m_dist[u] = INF;
    }

    m_dist[NIL] = INF;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        if (m_dist[u] < m_dist[NIL])
        {
            std::list<int>::iterator it;
            for (it = m_adj[u].begin(); it != m_adj[u].end(); ++it)
            {
                int v = *it;

                if (m_dist[m_pairV[v]] == INF)
                {
                    m_dist[m_pairV[v]] = m_dist[u] + 1;
                    q.push(m_pairV[v]);
                }
            }
        }
    }

    return (m_dist[NIL] != INF);
}

bool PairFinder::Dfs(int u)
{
    if (u != NIL)
    {
        std::list<int>::iterator it;
        for (it = m_adj[u].begin(); it != m_adj[u].end(); ++it)
        {
            int v = *it;

            if (m_dist[m_pairV[v]] == m_dist[u] + 1)
            {
                if (Dfs(m_pairV[v]) == true)
                {
                    m_pairV[v] = u;
                    m_pairU[u] = v;
                    return true;
                }
            }
        }

        m_dist[u] = INF;
        return false;
    }
    return true;
}

int PairFinder::CountPair()
{
    m_pairU = std::vector<int>(m_uSize + 1, NIL);

    m_pairV = std::vector<int>(m_vSize + 1, NIL);

    m_dist = std::vector<int>(m_uSize + 1);

    int result = 0;

    while (Bfs())
        for (int u = 1; u <= m_uSize; u++)
            if (m_pairU[u] == NIL && Dfs(u))
                result++;
    
    return result;
}
