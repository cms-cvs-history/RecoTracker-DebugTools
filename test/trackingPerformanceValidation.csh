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
set RefRelease=CMSSW_1_3_3
set RefSelection=out_of_the_box
set NewSelection=out_of_the_box
#set Sequence=digi2track
#set Sequence=re_tracking
set Sequence=only_validation
set samples=(RelValMinBias RelValHiggsGammaGammaM120 RelValBJets_Pt_50_120 RelValTTbar RelValQCD_Pt_80_120 RelValQCD_Pt_3000_3500 RelValZPrimeEEM1000 RelValZPrimeEEM4000)
#set samples=(RelVal-RelVal123QCD_pt80_120)
#####################
set RELEASE=$CMSSW_VERSION
set WWWDIR=/afs/cern.ch/cms/performance/tracker/activities/reconstruction/tracking_performance


if($1 == 1) then
echo "you choosed option 1"

foreach sample($samples)

    if(! -d $RefRelease) mkdir $RefRelease
    if(! -d output_trees) mkdir output_trees
    cp $WWWDIR/$RefRelease/$RefSelection/$sample/val.$sample.root $RefRelease
    cp $WWWDIR/$RefRelease/$RefSelection/$sample/$sample.cff .

    if($sample == RelValZPrimeEEM4000) then
    sed s/NEVENT/500/g trackingPerformanceValidation.cfg >! tmp1.cfg
    else if($sample == RelValQCD_Pt_3000_3500) then
    sed s/NEVENT/100/g trackingPerformanceValidation.cfg >! tmp1.cfg
    else
    sed s/NEVENT/500/g trackingPerformanceValidation.cfg >! tmp1.cfg
    endif

    sed s/SEQUENCE/$Sequence/g tmp1.cfg >! tmp2.cfg
    sed s/SAMPLE/$sample/g tmp2.cfg >! $sample.cfg

touch $sample.cff

end

else if($1 == 2) then
echo "you choosed option 2"

foreach sample($samples)

eval `scramv1 run -csh`
cmsRun $sample.cfg >& ! $sample.log &


end

else if($1 == 3) then
echo "you choosed option 3"
foreach sample($samples)

    sed s~NEW_FILE~val.$sample.root~g TracksCompare.C >! tmp1.C
    sed s~REF_FILE~$RefRelease/val.$sample.root~g tmp1.C >! tmp2.C
    sed s~REF_LABEL~$sample~g tmp2.C >! tmp3.C
    sed s~NEW_LABEL~$sample~g tmp3.C >! tmp4.C
    sed s~REF_RELEASE~$RefRelease~g tmp4.C >! tmp5.C
    sed s~NEW_RELEASE~$RELEASE~g tmp5.C >! tmp6.C
    sed s~REFSELECTION~$RefSelection~g tmp6.C >! tmp7.C
    sed s~NEWSELECTION~$NewSelection~g tmp7.C >! tmp8.C
    sed s~TracksCompare~$sample~g tmp8.C >! $sample.C

    root -b -q $sample.C > ! macro.$sample.log

    if ( ! -d $WWWDIR/$RELEASE) mkdir $WWWDIR/$RELEASE
    if ( ! -d $WWWDIR/$RELEASE/$NewSelection) mkdir $WWWDIR/$RELEASE/$NewSelection
    if ( ! -d $WWWDIR/$RELEASE/$NewSelection/$sample) mkdir $WWWDIR/$RELEASE/$NewSelection/$sample

    echo "copying pdf files for sample: " $sample
    cp *.pdf $WWWDIR/$RELEASE/$NewSelection/$sample

    echo "copying root file for sample: " $sample
    cp val.$sample.root $WWWDIR/$RELEASE/$NewSelection/$sample

    echo "copying cff file for sample: " $sample
    cp $sample.cff $WWWDIR/$RELEASE/$NewSelection/$sample
    
    rm tmp*.C
    rm *.pdf

end




else if($1 == 4) then
foreach sample( $samples)

  cp $sample.cff $WWWDIR/$RefRelease/$Selection/$sample/
end

else
    echo "you have to choose between option 1 and option 2"
endif


