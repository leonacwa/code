void spfa() {
    d[S]=0;
    v[S]=true;
    deque <int> q;
    for(q.push_back(S);!q.empty();) {
        int x=q.front();
        q.pop_front();
        for(int k=head[x];k!=-1;k=el[k].next) {
            int y=el[k].y;
            if(d[y]>d[x]+el[k].c) {
                d[y]=d[x]+el[k].c;
                if(!v[y]) {
                    v[y]=true;
                    if(!q.empty()) {
                        if(d[y]>d[q.front()])
                            q.push_back(y);
                        else
                            q.push_front(y);
                    }
                    else
                        q.push_back(y);
                }
            }
        }
        v[x]=false;
    }
    return ;
}