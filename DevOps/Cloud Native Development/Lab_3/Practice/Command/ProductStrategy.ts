import {Wafer} from './Wafer';
import {Subrecipe} from './Subrecipe';

export interface ProductStrategy{
		genSubrecipe(wafer: Wafer): Subrecipe;
}

export class MPStrategy implements ProductStrategy{
		public genSubrecipe(wafer: Wafer): Subrecipe
		{
				return new Subrecipe('APC Subrecipe for[' + wafer.id + ']: A+B*(Fn of MobilePhone)');				
		}
}

export class PCStrategy implements ProductStrategy{
		public genSubrecipe(wafer: Wafer): Subrecipe
		{
				return new Subrecipe('APC Subrecipe for[' + wafer.id + ']: A+B*(Fn of PersonalComputer)');
		}
}

export class NBStrategy implements ProductStrategy{
		public genSubrecipe(wafer: Wafer): Subrecipe
		{
				return new Subrecipe('APC Subrecipe for[' + wafer.id + ']: A+B*(Fn of NoteBook)');
		}
}

