import {Wafer} from './Wafer';
import {Subrecipe} from './Subrecipe';

export interface TeachStrategy{
    genTeach(): string;
}

export class N7Strategy implements TeachStrategy{
		public genTeach(): string
		{
				return "N7";				
		}
}

export class N5Strategy implements TeachStrategy{
    public genTeach(): string
    {
            return "N5";				
    }
}

export class N3Strategy implements TeachStrategy{
    public genTeach(): string
    {
            return "N3";				
    }
}