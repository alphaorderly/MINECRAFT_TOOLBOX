if [ -f saved ]
then
    cp ./init_save/banned-ips.json banned-ips.json
    cp ./init_save/banned-players.json banned-players.json
    cp ./init_save/bukkit.yml bukkit.yml
    cp ./init_save/commands.yml commands.yml
    cp ./init_save/ops.json ops.json
    cp ./init_save/paper.yml paper.yml
    cp ./init_save/permissions.yml permissions.yml
    cp ./init_save/server.properties server.properties
else
    true
fi