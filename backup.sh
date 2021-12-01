if [ -d world ]
then
    folder=$(date +"%Y-%m-%d-%H-%M-%S")
    foldername="${folder}BACKUP"
    mkdir $foldername

    cp -r ./world ./$foldername/world
    cp -r ./world_nether ./$foldername/world_nether
    cp -r ./world_the_end ./$foldername/world_the_end 
    cp -r ./plugins ./$foldername/plugins
else
    true
fi