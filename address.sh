#!/bin/bash


echo "------------Student Database------------"

create()
{
    echo -n "Enter Database Name: "
    read ab
    if [ -f $ab ] #checking if file is already present or not
    then
        echo -e "\nFile already exists !" 
    else
        touch $ab #creating a empty file
        echo "Student Database created."
    fi
}

display()
{
    echo -n "Enter Database Name: "
    read ab

    if [ -f $ab ] #checking if file is already present or not
    then
        if [ -s $ab ] #checking if file is empty or not
        then
            echo -e "Roll No.| Student Name\t| Email\t\t| Mobile Number\n"
            sed -i '/^$/d' $ab #checking and removing empty lines
            cat $ab #outputting the file 
        else
            echo "Error : No Records !"
        fi
    else 
        echo -e "\nFile doesn't exists !" 
    fi
}
insert()
{
    echo -n "Enter Database Name: "
    read ab

    if [ -f $ab ] #checking if file is already present or not
    then
        echo -n "Enter Roll no. : "
        read roll_no
        if grep -q $roll_no $ab; #checking whether the roll no exists in the file
        then 
            echo "Error : Roll No. already exists !"
        else
            echo "Enter Name,email and mobile number : "
            read name email mobile

            line=`echo $roll_no $name $email $mobile`

            echo $line >> $ab #appending the data to the file
            echo "Record Inserted"
        fi
    else  
        echo -e "\nFile doesn't exists !" 
    fi
}
modify(){
    echo -n "Enter Database Name: "
    read ab
    if [ -f $ab ] #checking if file is already present or not
    then 
        echo -n "Enter Roll No. : "
        read roll_no

        if grep -q $roll_no $ab;  #checking whether the roll no exists in the file
        then 
            old=`cat $ab | grep $roll_no`

            array=($old)
            new=""
            echo -n "Enter modified Mobile Number: "
            read mobile
            array[3]=$mobile
            for val in ${array[@]};
            do
                echo $val
                new+="$val "
            done
            echo "Old Record : $old"
            echo "New Record : $new"

            sed -i s/"$old"/"$new"/g $ab  #replacing the old entry with new entry 
            echo -e "\nRecord Modified!\n"
        else
            echo "Error : Roll No. does not exists !"
           
        fi
    else  
        echo -e "\nFile doesn't exists !" 
    fi
}
delete(){
    echo -n "Enter Database Name: "
    read ab

    if [ -f $ab ] 
    then
        echo -n "Enter Roll No. : "
        read roll_no

        if grep -q $roll_no $ab; #checking whether the roll no exists in the file
        then 
            old=`cat $ab | grep $roll_no`

            echo "Record : $old"

            sed -i s/"$old"/""/g $ab  #replacing the old entry with blank space
            echo "Record Deleted!"
        else
            echo "Error :  does not exists !"
        fi
    else  
        echo -e "\nFile doesn't exists !" 
    fi
}

while true
do
    echo -e "\n1.Create"
    echo "2.Display"
    echo "3.Insert"
    echo "4.Modify"
    echo "5.Delete"
    echo "6.Exit"

    echo -e -n "\nEnter choice: "
    read  choice

    case $choice in 
        1 )
            echo -e "\n----------------"
            create
            echo "----------------"
        ;;
        2 )
            echo -e "\n----------------"
            display
            echo "----------------"
        ;;
        3 )
            echo -e "\n----------------"
            insert
            echo "----------------"
        ;;
        4 ) 
            echo -e "\n----------------"
            modify
            echo "----------------"
        ;;
        5 ) 
            echo -e "\n----------------"
            delete
            echo "----------------"
        ;;
        6 )
            echo -e "\n----------------"
            echo "Exit"
            echo "----------------"
            exit
        ;;
        * )
            echo -e "\n----------------"
            echo "Enter proper choice !!"
            echo "----------------"
        ;;
    esac
done
