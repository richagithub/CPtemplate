int MAXSIZE = 0;
int treeSIZE = 0;

    int buildTree(int l, int r, int idx, vector<int>& nums, vector<int>& tree)  {
        if(l>r) return INT_MAX;

        treeSIZE = max(treeSIZE, idx);
        if(l==r)//leaf node
        {
            tree[idx] = nums[l];
            return tree[idx];
        }

        int mid = l+(r-l)/2;
        int left = buildTree( l, mid,(2*idx)+1, nums, tree);
        int right = buildTree( mid+1, r ,(2*idx)+2, nums, tree);
        tree[idx] = max(left, right);
        return tree[idx];
    }

    int updateTree(int l, int r, int idx, int ll, int rr, int val, int lag,vector<int>& tree, vector<int>& lazy){
        if(l>r) return 0;
        //apply lag no matter what
        tree[idx] = max(tree[idx] - lag , 0);
         if(l < r && lag>0)
                {
                    lazy[idx] = lazy[idx] + lag;
                    // cout<<"lazy at "<<idx <<" is " <<lazy[idx]<<"\n";
                }

        //if no overlap
        if(r<ll ||l>rr)
            {
                // cout<<idx << "-out-"<< tree[idx]<<" l="<<l<<" r="<<r<<"\n";
                return tree[idx];
            }

        //l-r completely inside
        if(ll<=l && r<=rr){
            tree[idx] = max(tree[idx] - val, 0);
            lazy[idx] = lazy[idx] + val;
            // cout<<idx << "-in-"<< tree[idx]<<" l="<<l<<" r="<<r<<"\n";
            return tree[idx];
        }

        //if overlap
        if(lazy[idx] > 0){
            // val = val + lazy[idx];
            lag = lazy[idx];
            lazy[idx] = 0; 
            // cout<<"lazy at "<<idx <<" is " <<lazy[idx]<<"\n";
        }
        int mid = l+(r-l)/2;
        int left = updateTree(l,mid, 2*idx + 1, ll, rr, val,lag, tree, lazy);
        int right = updateTree(mid+1,r, 2*idx + 2, ll, rr, val, lag, tree, lazy);
        tree[idx] = max(left,right);
        // cout<<idx << "-ov-"<< tree[idx]<<" l="<<l<<" r="<<r<<"\n";
        return tree[idx];
    }


//caller main method :
//call build tree:
int n = nums.size();
MAXSIZE = 4*n;
vector<int> tree(MAXSIZE, INT_MAX);
vector<int> lazy(MAXSIZE, 0);
int rootval = buildTree(0,n-1, 0, nums, tree);


//update:
int ll = queries[i][0];
int rr = queries[i][1];
int val = queries[i][2];
// cout<<"next-\n";
int rootval = updateTree(0, n-1,0, ll,rr,val, 0, tree, lazy);



//view use : https://leetcode.com/problems/zero-array-transformation-ii/submissions/1572839063/
