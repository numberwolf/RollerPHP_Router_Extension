#git add -A;
#git commit -m $(date +%Y%m%d);
#git push -u origin master;
#read -p "此次上传:"  val
##echo $val
#git commit -m $val
#git push origin --all
#git push origin master

COMMIT_VAL=""
DATE=$(date +%Y%m%d)

function github {
	mv .git/config.github.com .git/config
	git add -A
	read -p "commit:" val
	COMMIT_VAL=${val}",date:"${DATE}
	git commit -m ${COMMIT_VAL}
	git push origin master
	mv .git/config .git/config.github.com
}

function coding {
	mv .git/config.coding.net .git/config
	git add -A
	git commit -m ${COMMIT_VAL}
	git push origin master
	mv .git/config .git/config.coding.net
}

function main {
	github
	coding
}

main

