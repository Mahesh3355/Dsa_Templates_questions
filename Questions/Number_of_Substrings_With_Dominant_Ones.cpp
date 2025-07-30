// You are given a binary string s.
// Return the number of substrings with dominant ones.
// A string has dominant ones if the number of ones in the string is greater than or equal to the square of the number of zeros in the string.
class Solution {
public:
    int numberOfSubstrings(string s) {
        int one=0,n=s.length(),ans=0;
        vector<int> zero;
        int tone=0;
        for(int i=0;i<n;i++)
        {
            if(s[i]=='0')
            {
               ans+=(tone*(tone+1))/2;
               tone=0;
               zero.push_back(i);
            }
            else
            {
                one++;
                tone++;
            }
        }
        ans+=(tone*(tone+1))/2;
        zero.push_back(n);
        zero.insert(zero.begin(),-1);
        int l=min(int(sqrt(one)),n-one);
        for(int i=1;i<=l;i++)
        {
            if(i>(zero.size()-2))
            {
                break;
            } 
            int need=i*i,j=1,k=1,tone=0;
            while(k<zero.size()-1)
            {
                if((k-j+1)==i)
                {
                    int rem=need-tone;
                    int lo=zero[j]-zero[j-1]-1,ro=zero[k+1]-zero[k]-1;
                    for(int p=0;p<=lo;p++)
                    {
                        int trem=rem-p;
                        if(trem>ro) continue;
                        if(trem<=0)
                        {
                            ans+=(ro+1);
                        }
                        else
                        {
                            ans+=(ro-trem+1);
                        }
                    }
                    tone-=(zero[j+1]-zero[j]-1);
                    j++;
                }
                tone+=(zero[k+1]-zero[k]-1);
                k++;
            }

        }
        return ans;
    }
};
