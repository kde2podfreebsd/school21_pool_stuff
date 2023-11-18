ls ./ai_help
chmod 744 ./ai_help/keygen.sh
chmod 744 ./ai_help/unifier.sh
./ai_help/keygen.sh
cd ./key
rm file*
for i in part*      
do
cat $i >> main.key
done
rm part*
cd ..
mv ./key ./ai_help
