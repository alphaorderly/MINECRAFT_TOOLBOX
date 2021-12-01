if [ -f saved ]
then
    true
else
    mkdir init_save
    cp banned-ips.json ./init_save/banned-ips.json
    cp banned-players.json ./init_save/banned-players.json
    cp bukkit.yml ./init_save/bukkit.yml
    cp commands.yml ./init_save/commands.yml
    cp ops.json ./init_save/ops.json
    cp paper.yml ./init_save/paper.yml
    cp permissions.yml ./init_save/permissions.yml
    cp server.properties ./init_save/server.properties
    echo "done" > saved
fi

folder="$(date +"%Y-%m-%d-%H-%M-%S")"
mkdir $folder

mv ./logs/* ./$folder