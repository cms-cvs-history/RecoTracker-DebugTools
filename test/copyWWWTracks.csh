#! /bin/csh 

######################
set RefRelease=CMSSW_1_7_0
set FilterType=out_of_the_box

#####################

# selection should be something like:
# "out_of_the_box
# "dummy_selection"
# "smart_selection"

#echo "type of selection: " $1

# sample should be something lik:
# RelValTTbar
# SingleMuonsPt1

#echo "type of samples: " $2


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
#cmsRun $sample.cfg >& $sample.log &

end

else if($1 == 2) then
echo "you choosed option 2"


#    if ( ! -d /afs/cern.ch/cms/performance/tracker/activities/reconstruction/tracking_performance/$RELEASE) mkdir /afs/cern.ch/cms/performance/tracker/activities/reconstruction/tracking_performance/$RELEASE
    
#    setenv WWWDIRObj /afs/cern.ch/cms/performance/tracker/activities/reconstruction/tracking_performance/$RELEASE/$1
    
#    if (! -d $WWWDIRObj) mkdir $WWWDIRObj
    
#    setenv WWWDIR $WWWDIRObj/$2
    
#    if (! -d $WWWDIRObj/$2) mkdir $WWWDIRObj/$2
    
#    mv *.pdf $WWWDIRObj/$2
else
    echo "you have to choose between option 1 and option 2"
endif


