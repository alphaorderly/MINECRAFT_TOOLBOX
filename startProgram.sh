
# If there's no java on pc, then install it - or check it is proper version

sudo apt install openjdk-17-jdk

# If there's no essential file, then download it and change its name.

if [ -f server.jar ]; then
    true
else
    wget -c https://papermc.io/api/v2/projects/paper/versions/1.17.1/builds/388/downloads/paper-1.17.1-388.jar -O server.jar
fi

# If server wasnt runned past time, download config file

if [ -f server.properties ]; then
    true
else
    java -jar server.jar
    rm eula.txt
    echo "eula=true" > eula.txt
fi

./mcsv

clear