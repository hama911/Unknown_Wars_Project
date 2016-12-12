#include "DxLib.h"
#include "AdvancedMath.h"
#include "AdvancedDraw.h"
#include "AdvancedSystem.h"
#include "Vec2.h"
#include "Color.h"
#include "Vec3.h"
#define DIVISION_MEMBER_MAX 5

class Power;
class Unit;
class Division;

class Mission
{
public:
	void set(Vec2 _pos, Power* _power = NULL)
	{
		Enabled = true;
		JoinedPower = _power;
		JoinedDivision = NULL;
		for (auto& connect : ConnectMissions)
			connect = NULL;
	}

	void update()
	{
		if (!Enabled) return;
	}
	void draw()
	{

	}


	bool Enabled = false;
	Power* JoinedPower;			//制圧している勢力
	Division* JoinedDivision;	//実行中のディビジョン
	Mission* ConnectMissions[10];	//隣接しているミッション
	Vec2 Position;
};

class Power
{
public:


	bool Enabled;	//有効かどうか
	Color color;	//勢力の色
};

class Unit
{
public:

	void update()
	{
		if (!Enabled) return;
		move();
		division();
		DrawPosition = DrawPosition*0.9 + Position*0.1;
		Vec2DrawAngle = (Vec2DrawAngle*0.9 + Vec2Angle*0.1).normalized();
	}


	void draw() const
	{
		if (!Enabled) return;
		DrawCircleAA(Position, 10, Color(255, 0, 0));
		DrawLineAA(Position, TargetPosition, Color(255, 0, 0), 5);
		DrawLineAA(Position, Position + Vec2Angle * 32, Color(255, 0, 0), 5);

		MV1SetUseZBuffer(ModelHandle, TRUE);
		MV1SetWriteZBuffer(ModelHandle, TRUE);
		//MV1SetPosition(ModelHandle, VGet(Position));
		MV1SetPosition(ModelHandle, VGet(DrawPosition));
		//MV1SetRotationXYZ(ModelHandle, VGet(0, float(Vec2Angle.angle()), 0));
		MV1SetRotationXYZ(ModelHandle, VGet(0, float(Vec2DrawAngle.angle()), 0));
		MV1DrawModel(ModelHandle);
		MV1SetScale(ModelHandle, VGet(0.2f, 0.2f, 0.2f));
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 128);
		//DrawCone3D(VGet(float(Position.x), 10.0f, float(-Position.y)), VGet(float(Position.x), 15.f, float(-Position.y)), 2, 30, JoinedPower->color.unsignedInt(), GetColor(255, 255, 255), true);
		DrawCone3D(VGet(float(DrawPosition.x), 10.0f, float(-DrawPosition.y)), VGet(float(DrawPosition.x), 15.f, float(-DrawPosition.y)), 2, 30, JoinedPower->color.unsignedInt(), GetColor(255, 255, 255), true);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	}

	void setTargetPosition(const Vec2& _tarPos, const Vec2& _tarAng = Vec2(1, 0), const bool _tarAngEnabled = false)
	{
		TargetPosition = _tarPos;
		TarAngEnabled = _tarAngEnabled;
		Vec2TargetAngle = _tarAng;
		MovingProgress = 0;
		MovingAngle = 0;
		MovingSpeed = 0;
		MovingSleepMode = false;
	}

	void move()	//移動処理全般
	{
		if (MovingSleepMode) return;
		if (MovingTimer != 0)
		{
			--MovingTimer;
			Vec2Angle.rotate(MovingAngle);
			Position += Vec2Angle*MovingSpeed;
			return;
		}
		else
		{
			++MovingProgress;
		}
		if (MovingProgress == 4)
		{
			Vec2Angle = Vec2TargetAngle;
			MovingSleepMode = true;
			return;
		}

		if (MovingProgress == 3)
		{
			Position = TargetPosition;
			if (TarAngEnabled)
			{
				const double angle = Vec2Angle.angle(Vec2TargetAngle);
				if (angle < 0)
				{
					MovingAngle = TurningSpeedMax;
				}
				else
				{
					MovingAngle = -TurningSpeedMax;
				}
				MovingSpeed = 0;
				MovingTimer = -int(angle / MovingAngle);
				return;
			}
			MovingSleepMode = true;
		}

		if (MovingProgress == 2)
		{
			MovingTimer = int(Position.distanceFrom(TargetPosition) / MovingSpeedMax);
			MovingSpeed = MovingSpeedMax;
			Vec2Angle = (TargetPosition - Position).normalized();
			MovingAngle = 0;
			return;
		}
		if (MovingProgress == 1)
		{
			const double angle = Vec2Angle.angle(TargetPosition - Position);
			if (angle < 0)
			{
				MovingAngle = TurningSpeedMax;
			}
			else
			{
				MovingAngle = -TurningSpeedMax;
			}
			MovingSpeed = 0;
			MovingTimer = -int(angle / MovingAngle);
			return;
		}
	}
	void MovingSetSleepMode()
	{
		MovingAngle = 0;
		MovingSpeed = 0;
		MovingTimer = 0;
		MovingSleepMode = true;
	}
	void set(const Vec2& _pos, const double& _ang, Power* _power = NULL)
	{
		reset();
		Enabled = true;
		JoinedPower = _power;
		Position = _pos;
		Vec2Angle.setFromAngle(_ang);
		DrawPosition = Position;
		Vec2DrawAngle = Vec2Angle;
	}
	void set(Power* _power, const double& _minX, const double& _minY, const double& _maxX, const double& _maxY, const double& _ang)
	{
		reset();
		Enabled = true;
		JoinedPower = _power;
		Position.x = Random(_minX, _maxX);
		Position.y = Random(_minY, _maxY);
		TargetPosition = Position;
		Vec2Angle.setFromAngle(_ang);
		DrawPosition = Position;
		Vec2DrawAngle = Vec2Angle;
	}
	void reset()
	{
		Enabled = false;
		JoinedPower = NULL;
		Position = 0;
		TargetPosition = 0;
		Vec2Angle = 1;
		Vec2TargetAngle = 1;
		Vec2DrawAngle = 1;
		DrawPosition = 0;
		MovingSleepMode = true;
		MovingProgress = 0;
		MovingTimer = 0;
		MovingSpeed = 0;
		MovingAngle = 0;
		ModelHandle = 0;
		MovingSpeedMax = 2.0;
		TurningSpeedMax = 0.03;
		JoinedDivision = NULL;
		IsLeaderUnit = false;
	}

	void division();

public:
	bool Enabled = false;

	Power*	JoinedPower;	//所属している勢力
	Vec2	Position;		//位置
	Vec2	TargetPosition;	//目標の位置
	Vec2	Vec2Angle;		//向いている方向
	Vec2	Vec2TargetAngle;
	Vec2	DrawPosition;	//実際に描画する位置
	Vec2	Vec2DrawAngle;	//実際に描画する方向

	//移動処理用
	int		MovingProgress;	//実行中の移動行動を示す
	bool	MovingSleepMode;//trueで移動処理をしない
	bool	TarAngEnabled;	//TargetAngleを使う
	int		MovingTimer;	//移動シーケンス用タイマー
	double	MovingSpeed;	//現在の移動速度
	double	MovingAngle;	//現在の角度速度

	double	MovingSpeedMax;	//最大移動速度
	double	TurningSpeedMax;//最大回転速度

	Division*	JoinedDivision;	//所属している師団
	bool	IsLeaderUnit;	//師団長に任命されているか否か

	//3Dモデル用
	int		ModelHandle;	//3Dモデルのハンドル
};


class Division
{
public:

	Vec2 getMemberTargetPosition(const Unit* member) const
	{
		for (int i = 0; i < DIVISION_MEMBER_MAX; i++)
		{
			if (member == MemberUnits[i])
			{
				return TargetPosition + Vec2TargetAngle.rotated(Pi / 2)*i * 16;
			}
		}
		return{ 0,0 };	//メンバーにいない、ということになるのでありえない状況
	}

	void update()
	{
		if (!Enabled) return;
	}

	void draw() const
	{
		if (!Enabled) return;
	}

	void reset()
	{
		Enabled = false;
		for (auto& unit : MemberUnits)
			unit = NULL;
		LeaderUnit = NULL;
		JoinedPower = NULL;
		NumMemberUnits = 0;
		Position = 0;
		TargetPosition = 0;
		Vec2Angle = 1;
		Vec2TargetAngle = 1;
	}

	void set()
	{
		Enabled = true;
	}
	void set(Power* power)
	{
		JoinedPower = power;
		Enabled = true;
	}

	bool joinDivision(Unit* unit);




private:
	bool Enabled = false;
	Power*	JoinedPower;	//所属している勢力
	Unit*	MemberUnits[DIVISION_MEMBER_MAX];	//メンバー
	Unit*	LeaderUnit;		//リーダーユニット
	int		NumMemberUnits;	//有効な総メンバー数
	Vec2	Position;
	Vec2	TargetPosition;
	Vec2	Vec2Angle;
	Vec2	Vec2TargetAngle;
};


#define UNIT_MAX 100
#define DIVISION_MAX 100
#define MISSION_MAX 100
#define POWER_MAX 2
Power powers[POWER_MAX];
Unit units[UNIT_MAX];
Division divisions[DIVISION_MAX];
Mission missions[MISSION_MAX];


bool Division::joinDivision(Unit* unit)
{
	if (!Enabled) return false;
	if (NumMemberUnits == DIVISION_MEMBER_MAX) return false;	//最大メンバー数に達しているため
	if (JoinedPower != unit->JoinedPower) return false;
	for (auto& member : MemberUnits)
	{
		if (member == NULL)
		{
			member = unit;
			unit->JoinedDivision = this;
			if (LeaderUnit == NULL)
			{
				//もし、師団長がいない場合は任命
				LeaderUnit = unit;
				unit->IsLeaderUnit = true;
				//師団長の情報を位置情報にインプット
				Position = unit->Position;
				TargetPosition = unit->Position;
				Vec2Angle = unit->Vec2Angle;
				Vec2TargetAngle = unit->Vec2Angle;
				//リーダーユニットの移動情報をリセット
				unit->MovingSetSleepMode();
			}
			else
			{
				unit->setTargetPosition(getMemberTargetPosition(unit), Vec2TargetAngle, true);
			}

			++NumMemberUnits;
			return true;
		}
	}
	return true;
}

void Unit::division()
{
	if (JoinedDivision == NULL)
	{
		for (auto& division : divisions)
		{
			if (division.joinDivision(this))
			{
				break;
			}
		}
	}
	if (JoinedDivision == NULL) return;	//でも入れていないなら離脱

}


bool CameraGripLeftEnabled = false;		//カメラが画面をグリップしているかどうか
bool CameraGripRightEnabled = false;		//カメラが画面をグリップしているかどうか
Vec2 GripMousePos;
Vec3 CameraGroundPos(640, 0, -384);	//地面に位置するカメラ地点
Vec3 CameraTargetPos(640, 0, -384);	//地面に位置するカメラ地点
Vec3 CameraAirPos(0, 512, 512);		//空中のカメラ地点
Vec3 CameraTargetAirPos(0, 512, 512);
Vec3 CameraDeltaV;					//カメラに最終的に入力されるべき最終的なベクトル
Vec3 MouseGripPos;					//前回のグリップしていた地点
double CameraLength = 1024;			//地面からの距離
double CameraTargetLength = 1024;	//目標距離
double RotateY = 0;
double RotateX = 0;
Vec3 CameraPos()
{

	return CameraGroundPos + CameraAirPos;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Window設定
	ChangeWindowMode(TRUE);
	SetMainWindowText("Unknown Wars");
	SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(1280, 760, 16);

	if (DxLib_Init() == -1) return 0;

	//ミッションの設定
	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			missions[x + y*x].set()
		}
	}

	//勢力の設定
	powers[0].Enabled = true;
	powers[0].color.setFromHSV(Random(360));
	powers[1].Enabled = true;
	powers[1].color.setFromHSV(Random(360));

	//師団の生成
	for (auto& division : divisions) division.reset();
	for (int i = 2; i < 4; i++)
		divisions[i].set(&powers[0]);
	for (int i = 0; i < 2; i++)
		divisions[i].set(&powers[1]);

	//ユニットの生成
	for (auto& unit : units) unit.reset();
	for (int i = 0; i < 10; i++)
		units[i].set(&powers[0], 0, 0, 1280, 768, Random(Pi));
	for (int i = 10; i < 20; i++)
		units[i].set(&powers[1], 0, 0, 1280, 768, Random(Pi));

	//ユニットのモデル読み込み
	int MHandle = MV1LoadModel("二号戦車.mqo");
	for (auto& unit : units) unit.ModelHandle = MV1DuplicateModel(MHandle);

	SetCameraPositionAndTarget_UpVecY(VGet(640, 512, -1024), VGet(640, 0, -384));


	while (ProcessMessage() == 0)
	{
		SetCameraNearFar(0.1f, 10000.0f);
		//ユニットの処理
		for (auto& unit : units)
			unit.update();

		ClearDrawScreen();

		//カメラ処理
		SetCameraPositionAndTarget_UpVecY(CameraPos().VEC(), CameraGroundPos.VEC());
		int Mx, My;
		GetMousePoint(&Mx, &My);
		Vec3 StartPos(ConvScreenPosToWorldPos(VGet(float(Mx), float(My), 0.0f)));
		Vec3 EndPos(ConvScreenPosToWorldPos(VGet(float(Mx), float(My), 1.0f)));
		Vec3 GripGroundPos;
		GripGroundPos.x = StartPos.x - (StartPos.x - EndPos.x) * StartPos.y / (StartPos.y - EndPos.y);
		GripGroundPos.y = 0;
		GripGroundPos.z = StartPos.z - (StartPos.z - EndPos.z) * StartPos.y / (StartPos.y - EndPos.y);
		if ((GetMouseInput()&MOUSE_INPUT_RIGHT) != 0)
		{
			if (!CameraGripRightEnabled)
			{
				CameraGripRightEnabled = true;
				GripMousePos = MousePos();
			}
			RotateY += (GripMousePos - MousePos()).x*0.002;
			GripMousePos = MousePos();
		}
		else
		{
			CameraGripRightEnabled = false;
		}
		if ((GetMouseInput()&MOUSE_INPUT_LEFT) != 0)
		{
			if (!CameraGripLeftEnabled)
			{
				CameraGripLeftEnabled = true;
				MouseGripPos = GripGroundPos;
			}
			CameraDeltaV = (MouseGripPos - GripGroundPos) * 5;
		}
		else
		{
			CameraGripLeftEnabled = false;
		}
		DrawFormatString(0, 0, GetColor(255, 255, 255), "x = %.3f y = %.3f z = %.3f", CameraTargetAirPos.x, CameraTargetAirPos.y, CameraTargetAirPos.z);
		//マウスホイールに関する処理
		const double Wheel = GetMouseWheelRotVol();
		CameraTargetAirPos = CameraTargetAirPos + (-CameraTargetAirPos)*(Wheel*0.1);
		CameraAirPos += (CameraTargetAirPos - CameraAirPos)*0.1;
		CameraTargetAirPos -= (CameraTargetAirPos - CameraAirPos)*0.1;

		CameraTargetPos = CameraTargetPos + (GripGroundPos - CameraTargetPos)*(Wheel*0.1);
		CameraGroundPos += (CameraTargetPos - CameraGroundPos)*0.1;
		CameraTargetPos -= (CameraTargetPos - CameraGroundPos)*0.1;

		CameraAirPos.rotateY(RotateY*0.1);
		CameraTargetAirPos.rotateY(RotateY*0.1);
		RotateY -= RotateY*0.1;

		CameraGroundPos += CameraDeltaV * 0.1;
		CameraDeltaV -= CameraDeltaV*0.1;





		DrawTriangle3D(VGet(0, 0, 0), VGet(1280, 0, 0), VGet(0, 0, -768), 0x3344333, 1);
		DrawTriangle3D(VGet(1280, 0, -768), VGet(1280, 0, 0), VGet(0, 0, -768), 0x334433, 1);

		//MV1DrawModel(GrHandle);

		for (auto& unit : units)
			unit.draw();


		if (ScreenFlip() == -1) return 0;
	}

	//終了処理
	DxLib_End();
	return 0;
}
