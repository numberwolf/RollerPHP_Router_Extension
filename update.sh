git add -A;
#git commit -m $(date +%Y%m%d);
#git push -u origin master;
read -p "此次上传:"  val
##echo $val
git commit -m $val
git push origin --all
#git push origin master
#ssh -p 22 root@numberwolf.top 'cd /var/www/html/ME/ && git reset --hard && git pull origin master && chmod -R 777 ../ME/ && cd ../../ && ./write_me_db.sh'
