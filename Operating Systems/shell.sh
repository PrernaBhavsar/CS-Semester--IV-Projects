#!/bin/bash
while true; do
 
 echo -e"\nMain Menu" 
 echo -e "1.Global News\n2.Indian News\n3.Sports News\n4.Editors Pick\n"
 read -p 'Enter a choice: ' ch 
 
 if [ "$ch" = "1" ]
  then
   echo "http://www.bbc.com" | wget -O- -i- | hxnormalize -x | 
   hxselect -i "section.module--news" |  lynx -stdin -dump > globalnews 
   echo -e "\n\nGLOBAL NEWS\n\n" 
   cat globalnews
   
  elif [ "$ch" = "2" ]
   then
    echo "http://www.bbc.com" |wget -O- -i- | hxnormalize -x | 
    hxselect -i "section.module--regional-news" |  lynx -stdin -dump > Indiannews 
    echo -e "\n\nINDIAN NEWS\n\n"  
    cat Indiannews
    
  elif [ "$ch" = "3" ]
   then
    echo "http://www.bbc.com" | wget -O- -i- | hxnormalize -x | 
    hxselect -i "section.module--sport" |  lynx -stdin -dump > Sportsnews 
    echo -e "\n\nSPORTS NEWS\n\n" 
    cat Sportsnews
  
  elif [ "$ch" = "4" ]
   then
    echo "http://www.bbc.com" | wget -O- -i- | hxnormalize -x |
    hxselect -i "section.module--editors-picks" | lynx -stdin -dump > Editorsnews 
    echo "\n\nEDITOR'S PICKS\n\n" 
    cat Editorsnews
 
  else  
   echo -e "\nWrong choice\n"  
   break
  fi
done 
  
   
 
 
 
 

