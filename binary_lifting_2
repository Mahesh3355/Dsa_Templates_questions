 //Minimum Weighted Subgraph With the Required Paths II
//You are given an undirected weighted tree with n nodes, numbered from 0 to n - 1. It is represented by a 2D integer array edges of length n - 1,
//where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi.​Additionally, you are given a 2D integer array queries, where queries[j] = [src1j, src2j, destj].
//Return an array answer of length equal to queries.length, where answer[j] is the minimum total weight of a subtree such that it is possible to reach destj from both src1j and src2j using edges in this subtree.
//A subtree here is any connected subset of nodes and edges of the original tree forming a valid tree.
class Solution {
public:
    void dfs(vector<int>&nd,vector<int>&lv,vector<int>&pa,vector<vector<pair<int,int>>>&t,int sc,int dis,int lvl)
    {
        nd[sc]=dis;
        lv[sc]=lvl;
        for(auto i:t[sc])
        {
            if(nd[i.first]==-1)
            {
                pa[i.first]=sc;
                dfs(nd,lv,pa,t,i.first,dis+i.second,lvl+1);
            }
        }
    }
    void build(vector<vector<int>>&table,vector<int>&pa)
    {
        for(int i=0;i<table[0].size();i++)
        {
            table[0][i]=pa[i];
        }
        for(int i=1;i<17;i++)
        {
            for(int j=0;j<pa.size();j++)
            {
                table[i][j]=table[i-1][table[i-1][j]];
            }
        }
    }
    int query(int s,int k,vector<vector<int>>&table)
    {
        for(int i=0;i<17;i++)
        {
            if((1<<i)&k)
            {
                s=table[i][s];
            }
        }
        return s;
    }
    int dis(int s1,int s2,vector<int>&nd,vector<int>&lvl,vector<int>&pa,vector<vector<int>>&table)
    {
        if(lvl[s2]<lvl[s1]) swap(s1,s2);
        int x=s2,y=s1;
        if(lvl[s1]!=lvl[s2])
        x=query(s2,lvl[s2]-lvl[s1],table);
        if(y!=x)
        {
            for(int i=16;i>=0;i--)
            {
                  int yp=table[i][y];
                  int xp=table[i][x];
                  if(yp!=xp)
                  {
                       y=yp;
                       x=xp;
                  }
            }
            x=pa[x];
        }
        return nd[s1]+nd[s2]-2*nd[x];
    }
    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n=edges.size();
        n++;
        vector<vector<pair<int,int>>> t(n);
        vector<int> in(n,0);
        for(auto i:edges)
        {
            int u=i[0],v=i[1],w=i[2];
            t[u].push_back({v,w});
            t[v].push_back({u,w});
            in[u]++;
            in[v]++;
        }
        vector<int> nd(n,-1),ans,lvl(n,0),par(n,0);
        for(int i=0;i<n;i++)
        {
            if(in[i]==1)
            {
                dfs(nd,lvl,par,t,i,0,0);
                par[i]=i;
                break;
            }
        }
        vector<vector<int>> table(17,vector<int> (n));
        build(table,par);
        for(auto i:queries)
        {
            int s1=i[0],s2=i[1],d=i[2];
int dst=dis(s1,s2,nd,lvl,par,table)+dis(s1,d,nd,lvl,par,table)+dis(s2,d,nd,lvl,par,table);
            ans.push_back(dst/2);
        }
        return ans;
    }
};
