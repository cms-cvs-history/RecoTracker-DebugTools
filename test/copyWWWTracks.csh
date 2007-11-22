#! /bin/csh 

# selection should be something like:
# "out_of_the_box
# "dummy_selection"
# "smart_selection"

echo "type of selection: " $1

# sample should be something lik:
# RelValTTbar
# SingleMuonsPt1

echo "type of samples: " $2

setenv RELEASE $CMSSW_VERSION

if ( ! -d /afs/cern.ch/cms/performance/tracker/activities/reconstruction/tracking_performance/$RELEASE) mkdir /afs/cern.ch/cms/performance/tracker/activities/reconstruction/tracking_performance/$RELEASE

setenv WWWDIRObj /afs/cern.ch/cms/performance/tracker/activities/reconstruction/tracking_performance/$RELEASE/$1

if (! -d $WWWDIRObj) mkdir $WWWDIRObj

setenv WWWDIR $WWWDIRObj/$2

if (! -d $WWWDIRObj/$2) mkdir $WWWDIRObj/$2

mv *.pdf $WWWDIRObj/$2



