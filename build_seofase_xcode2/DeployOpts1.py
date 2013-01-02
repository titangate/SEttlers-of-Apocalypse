# coding=utf-8

###### Options ######

options={}

options["<config>"]=ur'Default'
options["<os>"]=ur'android'
options["appdata"]=ur'/Users/lolium/.config/marmalade/DeployTool'
options["build"]=ur'ARM GCC Release'
options["cmdline"]=['/Developer/Marmalade/6.1/s3e/makefile_builder/mkb.py', '--buildenv=xcode', '/Users/lolium/SEttlers-of-Apocalypse/SEofASE.mkb', '--deploy-only']
options["configlist"]=ur'Default ,'
options["deploymode"]=ur'Package, Install and Run'
options["device"]=ur'"{"localdir}/Deploy.py" device "{"tempdir}/DeployOpts.py" {hasmkb}'
options["dir"]=ur'/Users/lolium/SEttlers-of-Apocalypse/build_seofase_xcode'
options["folder"]=ur'"{"localdir}/Deploy.py" folder "{"tempdir}/DeployOpts.py" {hasmkb}'
options["hasmkb"]=ur'nomkb'
options["helpfile"]=ur'../docs/Deployment.chm'
options["helppage"]=ur'0'
options["lastdir"]=ur'/Users/lolium/SEttlers-of-Apocalypse/build_seofase_xcode'
options["mkb"]=ur'/Users/lolium/SEttlers-of-Apocalypse/SEofASE.mkb'
options["mkbdir"]=ur'/Users/lolium/SEttlers-of-Apocalypse'
options["mkbfile"]=ur'SEofASE.mkb'
options["outdir"]=ur'/Users/lolium/SEttlers-of-Apocalypse/build_seofase_xcode'
options["resdir"]=ur'/Developer/Marmalade/6.1/Applications/DeployTool.app/Contents/Resources/'
options["s3edir"]=ur'/Developer/Marmalade/6.1/s3e/'
options["stage"]=ur'build'
options["target"]=ur'SEofASE'
options["task"]=ur'Default'
options["tasktype"]=ur'Package, Install and Run'

###### Tasks ######

tasks=[]

### Task Default:android ###

t={}
tasks.append(t)
t["tasktype"]="Package, Install and Run"
t["<config>"]="Default"
t["os"]="android"
t["endDir"]="/Users/lolium/SEttlers-of-Apocalypse/build_seofase_xcode/deployments/default/android/release/arm"
