import { FoodLog } from './foodlog'
import { Entity, ObjectIdColumn, Column, PrimaryColumn } from 'typeorm'

@Entity()
export class Device {
	@ObjectIdColumn()
	_id?: string

	@Column()
	name!: string

	@Column()
	amount!: number

	@Column()
	logs!: FoodLog[]
}
