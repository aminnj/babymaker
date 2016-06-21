final_dir="ready"
files="
package.tar.gz 
main.exe 
liblooperBatch.so 
CORE 
LinkDef_out_rdict.pcm 
goldenJson_2015_2p26fb_2016_2p6fb.txt
"
mkdir -p $final_dir
tar -czf $files
cp condor_executable.sh $final_dir
mv package.tar.gz  $final_dir
echo "I put stuff into $final_dir! Use an instructions.txt line like:\n"
echo "BABY FA v1.00 <dataset> $(pwd)/$final_dir/package.tar.gz $(pwd)/$final_dir/condor_executable.sh"
