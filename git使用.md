
** Git revert 撤销某个提交版本
Git的一些常用的撤销提交版本的的命令：

git revert HEAD                  撤销前一次 commit  
git revert HEAD^               撤销前前一次 commit  
git revert commit （比如：fa042ce57ebbe5bb9c8db709f719cec2c58ee7ff）撤销指定的版本，撤销也会作为一次提交进行保存。  


** git reset 回退以前某个版本  
git reset是指将当前head的内容重置，不会留log信息。 

git reset HEAD filename  从暂存区中移除文件  
git reset –-hard HEAD~3  会将最新的3次提交全部重置，就像没有提交过一样。  
git reset -–hard commit (38679ed709fd0a3767b79b93d0fba5bb8dd235f8) 回退到 38679ed709fd0a3767b79b93d0fba5bb8dd235f8 版本  
根据-–soft -–mixed –hard，会对working tree和index和HEAD进行重置:  

git reset –-mixed：此为默认方式，不带任何参数的git reset，即时这种方式，它回退到某个版本，只保留源码，回退commit和index信息  
git reset –-soft：回退到某个版本，只回退了commit的信息，不会恢复到index file一级。如果还要提交，直接commit即可 
git reset –-hard：彻底回退到某个版本，本地的源码也会变为上一个版本的内容  

