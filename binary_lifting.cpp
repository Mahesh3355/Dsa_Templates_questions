class TreeAncestor {
public:
    vector<vector<int>> table;
    TreeAncestor(int n, vector<int>& parent) {
        table.resize(17, vector<int>(n));
        for(int i=0;i<n;i++)
        {
            table[0][i]=parent[i];
        }
        for(int i=1;i<17;i++)
        {
            for(int j=0;j<n;j++)
            {
                int x=table[i-1][j];
                if(x!=-1)
                table[i][j]=table[i-1][x];
                else
                table[i][j]=-1;
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        for(int i=0;i<17;i++)
        {
            if((1<<i)&k)
            {
                if(node!=-1)
                node=table[i][node];
            }
        }
        return node;
    }
};
