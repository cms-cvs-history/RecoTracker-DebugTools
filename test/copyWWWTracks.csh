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
set FilterType=out_of_the_box

#####################




if($1 == 1) then
echo "you choosed option 1"
set RELEASE=$CMSSW_VERSION
set WWWDIR=/afs/cern.ch/cms/performance/tracker/activities/reconstruction/tracking_performance

foreach sample( RelValMinBias RelValHiggsGammaGammaM120 RelValBJets_Pt_50_120 RelValTTbar RelValQCD_Pt_80_120 RelValQCD_Pt_3000_3500 RelValZPrimeEEM1000 RelValZPrimeEEM4000)

    if(! -d $RefRelease) mkdir $RefRelease
    if(! -d $RELEASE) mkdir $RELEASE
    cp $WWWDIR/$RefRelease/$FilterType/$sample/val.$sample.root $RefRelease

    if($sample != RelValZPrimeEEM4000) then
    sed s/NEVENT/2000/g trackingPerformanceValidation.cfg >! tmp1.cfg
    sed s/SAMPLE/$sample/g tmp1.cfg >! $sample.cfg
    else
    sed s/NEVENT/300/g trackingPerformanceValidation.cfg >! tmp1.cfg
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


#    if ( ! -d /afs/cern.ch/cms/performance/tracker/activities/reconstruction/tracking_performance/$RELEASE) mkdir /afs/cern.ch/cms/performance/tracker/activities/reconstruction/tracking_performance/$RELEASE
    
#    setenv WWWDIRObj /afs/cern.ch/cms/performance/tracker/activities/reconstruction/tracking_performance/$RELEASE/$1
    
#    if (! -d $WWWDIRObj) mkdir $WWWDIRObj
    
#    setenv WWWDIR $WWWDIRObj/$2
    
#    if (! -d $WWWDIRObj/$2) mkdir $WWWDIRObj/$2
    
#    mv *.pdf $WWWDIRObj/$2
else
    echo "you have to choose between option 1 and option 2"
endif


