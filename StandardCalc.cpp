#include <iostream>
#include <math.h>



class StandardCalc
{
public:

	float BoundTo180(float angle)
	{
		int sentinel = 0;

		if (angle < 0)
			sentinel = -1;
		else
			sentinel = 1;

		if (angle >= -180 && angle < 180)
			return angle;
		else
		{
			int flag = -1;
			angle = std::abs(angle);

			//the value of flag determines the position of the angle
			flag = int(angle / 180);

			if (flag % 2 == 0) //The angle is in the positive semi-circle
			{
				flag = int(angle / 90);
				if (flag % 2 == 1)
				{
					angle = (float(std::fmod(angle, 90) + 90));  //fmod return the remainder
				}
				else
					angle = float(std::fmod(angle, 90));
			}
			else //The angle is in the negative semi-circle
			{
				flag = int(angle / 90);
				if (flag % 2 == 1)
					angle = float(std::fmod(angle, 90) - 90);
				else
					angle = float(std::fmod(angle, 90) - 180);
			}
		}
		if (sentinel == -1)
			return -angle;
		else
			return angle;

	}

	bool IsAngleBetween(float first_angle, float middle_angle, float second_angle)
	{
		bool val = false;

		if (first_angle == second_angle)
			return val;

		float angles[4];

		angles[0] = first_angle;
		angles[1] = middle_angle;
		angles[2] = second_angle;
		angles[3] = 0;

		for (int i = 0; i < 3; i++)
		{
			//Testing if the input angles are bound to 180
			if ((angles[i] < -180) || (angles[i] > 180))
				std::cout << "FAILURE: " << angles[i] << " IS OUT OF THE RANGE [-180,180]" << std::endl;

			//Converting the angles into [0,360] form
			if (angles[i] < 0)
				angles[i] += 360;
		}

		if (angles[0] > angles[2])
		{
			angles[3] = angles[0] - angles[2];

			if ((360 - angles[3]) > angles[3])
			{
				if ((angles[0] > angles[1]) && (angles[2] < angles[1]))
					val = true;
			}

			else
			{
				if (((angles[0] < angles[1]) && (angles[1] <= 360)) || ((angles[2] > angles[1]) && (angles[1] >= 0)))
					val = true;
			}
		}

		else
		{
			angles[3] = angles[2] - angles[0];

			if ((360 - angles[3]) == angles[3])
			{
				if ((angles[1] != angles[0]) && (angles[1] != angles[2]))
					val = true;
			}

			if ((360 - angles[3]) > angles[3])
			{
				if ((angles[0] < angles[1]) && (angles[2] > angles[1]))
				{
					val = true;
				}
			}

			else
			{
				if (((angles[0] > angles[1]) && (angles[1] >= 0)) || ((angles[2] < angles[1]) && (angles[1] <= 360)))
					val = true;
			}
		}

			
		return val;
	}
};

#define TEST_EQ(EXPECTED, ACTUAL) \
    if (EXPECTED != ACTUAL) { \
        std::cout << "FAILURE: " << #ACTUAL << " gave " << ACTUAL << ", but expected " << EXPECTED << std::endl; \
    }

//Function Pre-declaration
void runTests();


	int main(int argc, char** argv)
	{
		//You can create an object and test the member functions here or modify the tests in the runTests() function

		runTests();

		return 0;
	}

	void runTests()
	{
		std::cout << "-------------" << std::endl;
		std::cout << "Failed Tests:" << std::endl;
		std::cout << "-------------" << std::endl;

		StandardCalc object;

		// Testing the BoundTo180() function
		TEST_EQ(0, object.BoundTo180(360));
		TEST_EQ(-90, object.BoundTo180(270));
		TEST_EQ(-90, object.BoundTo180(-450));

		//Testing the IsAngleBetween() function
		TEST_EQ(true, object.IsAngleBetween(-90,-180,110));
		TEST_EQ(false, object.IsAngleBetween(-90,-180,80));


		std::cout << "-------------" << std::endl;
	}
