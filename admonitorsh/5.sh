#!/bin/sh
#########################
#@author xujiang
#@date 2014-09-30
#@desc 
#########################
export PATH=/usr/lib64/qt-3.3/bin:/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/jdk/bin:/usr/local/maven/bin:/usr/local/protobuf/bin:/usr/local/hadoop/bin:/usr/local/hadoop/sbin:/usr/local/scala/bin:/usr/local/spark/bin:/usr/local/zookeeper/bin:/root/bin
export SCRIPT_PATH=`dirname $(readlink -f $0)` # get the path of the script
export LD_LIBRARY_PATH=/home/w/lib64
pushd . > /dev/null
cd "$SCRIPT_PATH"

N=0
if [ $# -gt 0 ]
then
	N=$1
fi

oldpath='/home/public/admonitorlogall'
newpath='/home/public/admonitorfiles'
workpath='./'
path='/home/public/admonitorcpp'

#to do
# make it only copy the data of one day
oldpath1='/home/public/admonitorlogs'
oldpath2='/home/public/admonitorloghttp'
date=` date +%Y%m%d `
for module in `ls $oldpath1`
do
	mkdir -p $oldpath/$module/
	cp $oldpath1/$module/*.conf *.conf.composite $oldpath/$module/
	cp $oldpath1/$module/*${date}.log $oldpath/$module/
done
for module in `ls $oldpath2`
do
	mkdir -p $oldpath/$module/
	cp $oldpath2/$module/*.conf *.conf.composite $oldpath/$module/
	cp $oldpath2/$module/*${date}.log $oldpath/$module/
done

modules=`ls $oldpath`

for((d=-$N;d<=0;d++))
do
	rm -f *.log *.txt *.conf *.composite
	date=` date +%Y%m%d -d "$d days"`
	d1=$[ $d - 1 ]
	date1=` date +%Y%m%d -d "$d1 days" `
	for module in $modules
	do
		cp -f $oldpath/$module/*${date}.log ./
		$path/merge.out $d $module `ls *.log`
		rm -f *.log
	done
	
	for module in $modules
	do
		cat $oldpath/$module/*.conf.composite|grep ^{.*}$ > ${module}.composite
	done
	$path/composite.out $modules
	rm *.composite

	for module in $modules
	do
		for width in 1 2 6 12
		do
			if [ `date +%w -d $date ` != 1 ]
			then
				cp -f $newpath/$date1/${module}w${width}.txt ./
			fi
			cat ${module}h${width}.txt >> ${module}w${width}.txt
		done

		if [ `date +%d -d $date ` != 01 ]
		then
			cp -f $newpath/$date1/${module}M1.txt ./
		fi
		cat ${module}d1.txt >> ${module}M1.txt

		if [ `date +%m%d -d $date ` != 0101 ]
		then
			cp -f $newpath/$date1/${module}y1.txt ./
		fi
		cat ${module}d1.txt >> ${module}y1.txt

		cp -f $newpath/$date1/${module}meta.conf ./
		timeinterval=`sed -n '4p' $oldpath/$module/*.conf | sed 's/[^0-9]//g'`
		$path/add.out ${module} ${timeinterval} ${module}meta.conf ${module}d1.txt
		cp mymeta.conf ${module}meta.conf
		cat mymeta.conf >> meta.conf
	done
	mkdir -p $newpath/$date
	mv *.txt $newpath/$date/
	mv meta.conf $newpath
#	rm *.conf
mv *.conf $newpath/$date/
done

popd  > /dev/null # return the directory orignal
