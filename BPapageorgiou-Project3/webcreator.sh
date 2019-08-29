#!/bin/bash    
rootdir=$1;filename=$2;w=$3;p=$4

#echo $rootdir $filename $w $p
if [ ! -d $rootdir ]
then 
	echo "No directory with name $rootdir"
elif [ ! -e $filename ]
then 
	echo "No file with name $filename"
elif [ "`echo $w | egrep ^[[:digit:]]+$`" = "" ]
then
	echo "w is not integer"
elif [ "`echo $p | egrep ^[[:digit:]]+$`" = "" ]
then
	echo "p is not integer"
else
	echo "sxedon ok"
	IFS_BAK=$IFS
  	l=0
	word=("")
	 
	IFS=$'\n'

	exec < "$2" 
	  # -r is needed to interpret the backslach characters as the part of
	  # the text in the file, and not as escape sequences
	while read -r line
	    do
	      l=$((l+1))
	      curr_line_char=${#line}
	      # set IFS to noraml field terminating characters
	      IFS=$IFS_BAK
	      read -a word <<< "$line"
	      # set IFS to \n only so that in the next read command
	      # only \n terminated lines at once are read
	      IFS=$'\n'
	done < "$2"
	   
	IFS=$IFS_BAK
	#echo $w
	#echo $l
	if [ $l -gt 10000 ]
	  	then
	  	echo "all ok"
	  	rm -rf $rootdir/*
	  	cd $rootdir
	  	let f=($p/2)+1
	  	let q=($w/2)+1
	  	declare -a ARRAY
	  	declare -a ARR
	  	i=0
	  	limit=50
	  	count=0
	  	while [ $i -lt $w ]
	  	do
	  		j=0
		  	while [ $j -lt $p ]
			do
				id=$(( $RANDOM % 20000*$p*$w + limit ))
				for ((koko=0; koko < count; koko++))
				do
					#echo $id
					#echo ${ARR[koko]}
					while [ $id -eq ${ARR[koko]} ]	
					do
						id=$(( $RANDOM % 20000*$p*$w + limit ))
					done
				done
				ARR[count]=$id
				ARRAY[count]=page${i}_${id}.html
				let j=j+1
				let count=count+1
			done
	  		let i=i+1
	  	done
	  	#echo ${ARRAY[*]}
	  	i=0
	  	count=0
	  	while [ $i -lt $w ]
	  	do
	  		echo Creating web site $i ...
	  		mkdir site$i
	  		cd site$i
			for ((koko=1; koko <= $p; koko++))
			do
				k=$(( $RANDOM % (l-2000) + 2))
	  			#echo $k
	  			m=$(( $RANDOM % 999 + 1001 ))
	  			#echo $m
	  			declare -a INTARR
				declare -a EXTARR
				fin=1
				qin=1

				while [ $fin -le $f ]
				do
					pos=$(( $RANDOM % 3 + $i*$p ))
					INTARR[fin-1]=${ARRAY[pos]}
					let fin=fin+1
				done
				let bound1=$i*$p
				let bound2=$i*$p+$p-1
				#echo ${INTARR[*]}
				while [ $qin -le $q ]
				do
					pos=$(( $RANDOM % ($w*$p) ))
					while [ $pos -ge $bound1 ] && [ $pos -le $bound2 ]
					do
							pos=$(( $RANDOM % ($w*$p) ))
					done
					EXTARR[qin-1]=${ARRAY[pos]}
					let qin=qin+1
				done
				#echo ${EXTARR[*]}

	  			let temp=$f+$q
	  			let lines=$m/$temp
	  			numlinks=0
	  			numlinks2=0
				echo Creating page $rootdir/site$i/${ARRAY[count]} starting at line $k ...
				touch ${ARRAY[count]}
				echo -e "<!DOCTYPE  html>\n<html>\n\t<body>\n\t" >> ${ARRAY[count]}
				IFS_BAK=$IFS
				word=("")
				 
				IFS=$'\n'
				linee=0;
				cd ../../
				#pwd
				exec < "$2" 
				  # -r is needed to interpret the backslach characters as the part of
				  # the text in the file, and not as escape sequences
				cur=$k
				let up=$k+$lines
				while read -r line
				    do
				      linee=$((linee+1))
				      #echo $line

				      if [ $linee -ge $k ]
				      then
				      	cd $rootdir/site$i
				      	echo -e "\t" >> ${ARRAY[count]}
				      	echo -e $line >> ${ARRAY[count]}
				      	let cur=cur+1
				      	if [ $cur -eq $up ]
				      	then
				      		let up=$up+$lines
				      		sel=$(( $RANDOM % 2 ))
				      		if [ $sel -eq 0 ]
				      		then
				      				if [ $numlinks -lt $f ]
				      				then
					      				echo "Adding internal link  to  $rootdir/site$i/${INTARR[numlinks]}"
										echo -e "<a href=${INTARR[numlinks]}>" >> ${ARRAY[count]}
										echo -e "${INTARR[numlinks]}" >> ${ARRAY[count]}
										let numlinks=numlinks+1
									else
										cd ../../
										continue;
									fi

							else
				      				if [ $numlinks2 -lt $q ]
				      				then
					      				start=5
					      				stop=6
					      				number=$(echo "${EXTARR[numlinks2]}" | cut -c $start-$(($stop-1)))
					      				echo "Adding external link  to  $rootdir/site$number/${EXTARR[numlinks2]}"
										echo -e "<a href=../site$number/${EXTARR[numlinks2]}>" >> ${ARRAY[count]}
										echo -e "${EXTARR[numlinks2]}" >> ${ARRAY[count]}
										let numlinks2=numlinks2+1
									else
										cd ../../
										continue;
									fi

							fi
							echo -e "</a>\n" >> ${ARRAY[count]}
						fi
						cd ../../
					  fi

				      # set IFS to noraml field terminating characters
				      IFS=$IFS_BAK
				      # set IFS to \n only so that in the next read command
				      # only \n terminated lines at once are read
				      IFS=$'\n'
				done < "$2"

				if [ $numlinks -lt $f ]
				then
					echo "Adding internal link  to  $rootdir/site$i/${INTARR[numlinks]}"
					echo -e "<a href=${INTARR[numlinks]}>" >> ${ARRAY[count]}
					echo -e "${INTARR[numlinks]}" >> ${ARRAY[count]}
					let numlinks=numlinks+1
				fi			
				if [ $numlinks2 -lt $q ]
				then
					start=5
					stop=6
					number=$(echo "${EXTARR[numlinks2]}" | cut -c $start-$(($stop-1)))
					echo "Adding external link  to  $rootdir/site$number/${EXTARR[numlinks2]}"
					echo -e "<a href=../site$number/${EXTARR[numlinks2]}>" >> ${ARRAY[count]}
					echo -e "${EXTARR[numlinks2]}" >> ${ARRAY[count]}
					let numlinks2=numlinks2+1
				fi	
				IFS=$IFS_BAK
				cd $rootdir/site$i
				#pwd
				echo -e "\t</body>\n</html>" >> ${ARRAY[count]}
				let count=count+1
			done
	  		let i=i+1
	  		cd ../
	  	done
	  	echo "All  pages  have  at  least  one  incoming  link"
	  	echo Done.
	fi

fi
