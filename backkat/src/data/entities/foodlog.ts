import { Entity, ObjectID, ObjectIdColumn, Column } from "typeorm"
import { ObjectId } from "mongodb"

@Entity()
export class FoodLog {
	@ObjectIdColumn()
	id?: ObjectID

	@Column()
	amount!: number

	@Column()
	moment?: Date
}