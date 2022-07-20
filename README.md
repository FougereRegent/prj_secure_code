## Network Clock

### 1./How to install the network clock ?

To install the network clock project you will run this command in root project

    sudo make

This command will compile this project and install these command : nc_client, ts, server_nc.

### 2./ How to use <i>server_nc</i> command

If you run the network clock server you will run into yout terminal this command

    nc_server

Now the nc_server open a command line wich allows 2 command <i>time</i> and <i>set</i>

    root@pc:~# server_nc
    > time "format_date"
    > set "your_date"

You can use the what you want, the date balise are describe below :

    Specifier 	Replaced By 	            Example
    %a 	Abbreviated weekday name 	        Sun
    %A 	Full weekday name 	                Sunday
    %b 	Abbreviated month name 	            Mar
    %B 	Full month name 	                March
    %c 	Date and time representation 	    Sun Aug 19 02:56:02 2012
    %d 	Day of the month (01-31) 	        19
    %H 	Hour in 24h format (00-23) 	        14
    %I 	Hour in 12h format (01-12) 	        05
    %j 	Day of the year (001-366) 	        231
    %m 	Month as a decimal number (01-12) 	08
    %M 	Minute (00-59) 	                    55
    %p 	AM or PM designation 	            PM
    %S 	Second (00-61) 	02
    %U 	Week number with the first Sunday as the first day of week one (00-53       33
    %w 	Weekday as a decimal number with Sunday as 0 (0-6) 	                    4
    %W 	Week number with the first Monday as the first day of week one (00-53) 	    34
    %x 	Date representation 	            08/19/12
    %X 	Time representation 	            02:50:06
    %y 	Year, last two digits (00-99)       01
    %Y 	Year 	                            2012
    %Z 	Timezone name or abbreviation 	    CDT
    %% 	A % sign 	                        %

the format to set the time are describe below:

    %H:%M:%S

The default port of this server is 8080 and he used the TCP protocol to established communication links with nc_client

### 2./How to use the nc_client ?

The nc_client is used to return the current date of nc_server.
To use this command you will run this command

    user@pc:~# nc_client "@IPV4" "port" "format_date"

The format date are describe above in <i>"How to use the network clock ?"</i> part.

### 3./ How to uninstall this program ?

To uninstall this program you will execute this command

    sudo make clean