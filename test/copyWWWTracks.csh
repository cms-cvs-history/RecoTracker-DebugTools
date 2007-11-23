#! /bin/csh 

## argv[1] == 1 
# copy reference files from afs and prepare cfg files

## argv[1] == 2
# submit cmsRun jobs


## argv[1] == 3 
# run the root macro

## argv[1] == 4 
# copy plots and root files to afs







######################
set RefRelease=CMSSW_1_7_0
set Selection=out_of_the_box

#####################
set RELEASE=$CMSSW_VERSION
set WWWDIR=/afs/cern.ch/cms/performance/tracker/activities/reconstruction/tracking_performance


if($1 == 1) then
echo "you choosed option 1"

foreach sample( RelValMinBias RelValHiggsGammaGammaM120 RelValBJets_Pt_50_120 RelValTTbar RelValQCD_Pt_80_120 RelValQCD_Pt_3000_3500 RelValZPrimeEEM1000 RelValZPrimeEEM4000)

    if(! -d $RefRelease) mkdir $RefRelease
    if(! -d output_trees) mkdir output_trees
    cp $WWWDIR/$RefRelease/$Selection/$sample/val.$sample.root $RefRelease

    if($sample == RelValZPrimeEEM4000) then
    sed s/NEVENT/1000/g trackingPerformanceValidation.cfg >! tmp1.cfg
    sed s/SAMPLE/$sample/g tmp1.cfg >! $sample.cfg
    else if($sample == RelValQCD_Pt_3000_3500) then
    sed s/NEVENT/300/g trackingPerformanceValidation.cfg >! tmp1.cfg
    sed s/SAMPLE/$sample/g tmp1.cfg >! $sample.cfg
    else
    sed s/NEVENT/2000/g trackingPerformanceValidation.cfg >! tmp1.cfg
    sed s/SAMPLE/$sample/g tmp1.cfg >! $sample.cfg
    endif

touch $sample.cff

end

else if($1 == 2) then
echo "you choosed option 2"

foreach sample( RelValMinBias RelValHiggsGammaGammaM120 RelValBJets_Pt_50_120 RelValTTbar RelValQCD_Pt_80_120 RelValQCD_Pt_3000_3500 RelValZPrimeEEM1000 RelValZPrimeEEM4000)

eval `scramv1 run -csh`
cmsRun $sample.cfg >& $sample.log &


end

else if($1 == 3) then
echo "you choosed option 3"
foreach sample( RelValMinBias RelValHiggsGammaGammaM120 RelValBJets_Pt_50_120 RelValTTbar RelValQCD_Pt_80_120 RelValQCD_Pt_3000_3500 RelValZPrimeEEM1000 RelValZPrimeEEM4000)

    sed s~NEW_FILE~val.$sample.root~g TracksCompare.C >! tmp1.C
    sed s~REF_FILE~$RefRelease/val.$sample.root~g tmp1.C >! tmp2.C
    sed s~REF_LABEL~$sample~g tmp2.C >! tmp3.C
    sed s~NEW_LABEL~$sample~g tmp3.C >! tmp4.C
    sed s~REF_RELEASE~$RefRelease~g tmp4.C >! tmp5.C
    sed s~NEW_RELEASE~$RELEASE~g tmp5.C >! tmp6.C
    sed s~SELECTION~$Selection~g tmp6.C >! tmp7.C
    sed s~TracksCompare~$sample~g tmp7.C >! $sample.C

    root -b -q $sample.C > macro.$sample.log

    if ( ! -d $WWWDIR/$RELEASE) mkdir $WWWDIR/$RELEASE
    if ( ! -d $WWWDIR/$RELEASE/$Selection) mkdir $WWWDIR/$RELEASE/$Selection
    if ( ! -d $WWWDIR/$RELEASE/$Selection/$sample) mkdir $WWWDIR/$RELEASE/$Selection/$sample

    echo "copying files for sample: " $sample
    mv *.pdf $WWWDIR/$RELEASE/$Selection/$sample

end






else
    echo "you have to choose between option 1 and option 2"
endif


