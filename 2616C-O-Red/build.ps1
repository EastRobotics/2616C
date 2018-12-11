$jsondata = Get-Content -Raw .\pros.json | ConvertFrom-Json

prosv5 make 
$LASTEXITCODE
if ($LASTEXITCODE -eq 0)
{
    if($jsondata.PROS.RunAfter){
        prosv5 upload --slot $jsondata.PROS.slot --name $jsondata.PROS.name --execute
    }else{
        prosv5 upload --slot $jsondata.PROS.slot --name $jsondata.PROS.name --run-screen
    }
}
if($jsondata.PROS.terminal){
  prosv5 terminal
}