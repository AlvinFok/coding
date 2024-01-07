import {Wafer} from './Wafer';
import {APC} from './APC';
import {ProcessTool} from './ProcessTool';



var apc = new AnotherAPC();
var processTool_a = new ProcessTool('A');
var wafer1 = new Wafer('N12345.00', 'Mobile Phone', 'ByProductStrategy');

//Client needs to know APC's logic for preview or execute...
//Any logic change will impact client call

//preview
apc.genSubrecipe(wafer);
apc.checkSubrecipeSpec(subrecipe);

//execute
apc.genSubrecipe(wafer);
apc.checkSubrecipeSpec(subrecipe);
apc.log(subrecipe);
apc.updateAPCModel(subrecipe);




