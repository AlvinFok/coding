import {Wafer} from './Wafer';
import {Subrecipe} from './Subrecipe';

export interface ProductStrategy{
	genType(): string;
}

export class MPStrategy implements ProductStrategy{
		public genType(): string
		{
				return 'MobilePhone';				
		}
}

export class PCStrategy implements ProductStrategy{
		public genType(): string
		{
				return 'PersonalComputer';
		}
}

export class NBStrategy implements ProductStrategy{
		public genType(): string
		{
				return 'NoteBook';
		}
}

