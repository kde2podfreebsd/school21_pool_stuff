chmod 744 ./ai_door_management_module.sh
mv ./door_management_fi ./door_management_files/
mkdir ./door_management_files/door_configuration
mkdir ./door_management_files/door_map
mkdir ./door_management_files/door_logs
mv ./door_management_files/*.conf ./door_management_files/door_configuration/ 
mv ./door_management_files/*.log ./door_management_files/door_logs
mv ./door_management_files/door_map_1.1 ./door_management_files/door_map/
