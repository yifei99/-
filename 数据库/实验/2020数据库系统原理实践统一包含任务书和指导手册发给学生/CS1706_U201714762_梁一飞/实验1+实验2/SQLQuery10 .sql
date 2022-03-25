/*Passenger*/
create TABLE Passenger(
PCardID char(18) PRIMARY KEY,
PName char(20),
Sex bit check (Sex=0 or Sex=1),
Age smallint
)
/*Station*/
create TABLE Station(
SID int PRIMARY KEY,
SName char(20),
CityName char(20)
)
/*Train*/
create TABLE Train(
TID int PRIMARY KEY,
SDATE date,
TName char(20),
SStationID int FOREIGN KEY REFERENCES Station(SID),
AStationID int FOREIGN KEY REFERENCES Station(SID),
STime datetime,
ATime datetime,
)
/*TrainPass*/
create TABLE TrainPass(
TID int,
SNO smallint,
SID int FOREIGN KEY REFERENCES STation(SID),
STime datetime,
ATime datetime,
PRIMARY KEY(TID,SNO)
)
/*TakeTrainRecord*/
create TABLE TakeTrainRecord(
RID int PRIMARY KEY,
PCardId char(18) FOREIGN KEY REFERENCES Passenger(PCardID),
TID int FOREIGN KEY REFERENCES Train(TID),
SStationID int FOREIGN KEY REFERENCES Station(SID),
AStationID int FOREIGN KEY REFERENCES Station(SID),
CarrigeID smallint,
SeatRow smallint,
SeatNo char(1) check(SeatNo in('A','B','C','D','E')),
SStatus int check (SStatus in (0,1,2))
)
/*DiagnoseRecord*/
create TABLE DiagnoseRecord(
DID int PRIMARY KEY,
PCardID char(18) FOREIGN KEY REFERENCES Passenger(PCardID),
DDay date,
DStatus smallint check(DStatus in (1,2,3)),
FDay date
)
/*TrainContactor*/
create TABLE TrainContactor(
CDate date,
CCardID char(18),
DStatus smallint check (DStatus in (1,2,3)),
PCardID char(18),
PRIMARY KEY(CDate,CCardID,DStatus,PCardID)
)

/*��*/
insert into TakeTrainRecord(RID,PCardID,TID,SStationID,AStationID,CarrigeID,SeatRow,SeatNo,SStatus) 
VALUES(33,'11011619880513219X',105,129,470,2,2,'A',0)
/*��*/
update TakeTrainRecord set SStatus=1
where RID=33
/*ɾ*/
delete from TakeTrainRecord
where RID=33
/*���������*/
create table WH_TakeTrainRecord(
   RID int PRIMARY KEY,
   PCardID char(18) REFERENCES Passenger(PCardID),
   TID int REFERENCES Train(TID),
   SStationID int REFERENCES Station(SID),
   AStationID int REFERENCES Station(SID),
   CarrigeID smallint,
   SeatRow smallint,
   SeatNo  char(1),
   SStatus int
)
INSERT INTO WH_TakeTrainRecord(RID,PCardID,TID,SStationID,AStationID,CarrigeID,SeatNo,SeatRow,SStatus) 
SELECT RID,PCardID,TID,SStationID,AStationID,CarrigeID,SeatNo,SeatRow,SStatus 
FROM TakeTrainRecord 
WHERE SStationID BETWEEN 1593 AND 1616
/*������ͼ*/
create view view_diagnose
as
  select DiagnoseRecord.PCardID,PName,Sex,TakeTrainRecord.TID,SDATE,CarrigeID,SeatRow,SeatNo
  from Passenger,TakeTrainRecord,Train,DiagnoseRecord
  where Passenger.PCardID=TakeTrainRecord.PCardID
  and Passenger.PCardID=DiagnoseRecord.PCardID
  and TakeTrainRecord.PCardID=DiagnoseRecord.PCardID
  and TakeTrainRecord.TID=Train.TID
  and DiagnoseRecord.DStatus=1
  and TakeTrainRecord.SStatus=1
go
/*������
create trigger newpatient
on DiagnoseRecord
after insert
as
begin
insert into TrainContactor(CDate,CCardID,DStatus,PCardID)
select	Train.SDATE,DiagnoseRecord.PCardID,2,TakeTrainRecord.PCardID
FROM DiagnoseRecord,TakeTrainRecord,Train
WHERE DiagnoseRecord.DStatus=1
and DiagnoseRecord.PCardID=TakeTrainRecord.PCardID
and TakeTrainRecord.TID=Train.TID
and 
end

create trigger newcontactor
on DiagnoseRecord
after insert
as
begin

end
*/

/*1.��ѯȷ���ߡ����������ڷ���ǰ14���ڵĳ˳���¼*/
select TakeTrainRecord.*
from TakeTrainRecord,Passenger,Train,DiagnoseRecord
where TakeTrainRecord.PCardID=Passenger.PCardID 
and Passenger.PName='����'
and TakeTrainRecord.TID=train.TID 
and DiagnoseRecord.PCardID=Passenger.PCardID
and Train.SDate
between DATEADD(DAY,-15,DiagnoseRecord.FDay) and DiagnoseRecord.FDay
/*2.��ѯ���дӳ��С��人�������ĳ˿ͳ��г�������ĳ�����*/
select  s2.cityname
from TakeTrainRecord ,Station s1 ,Station s2
where TakeTrainRecord.SStationID=s1.SID
and  TakeTrainRecord.AStationID=s2.SID
and s1.CityName='�人' 
/*3.����ÿλ�¹ڻ��ߴӷ�����ȷ���ʱ�����������������������Ϣ������������շ���ʱ�������Ľ�������*/
select Passenger.*,data=DATEDIFF("d",DiagnoseRecord.FDay,DiagnoseRecord.DDay)
from DiagnoseRecord,Passenger
where DiagnoseRecord.DStatus=1
and DiagnoseRecord.PCardID=Passenger.PCardID
order by DATEDIFF("d",DiagnoseRecord.FDay,DiagnoseRecord.DDay) DESC;
/*4.��ѯ��2020-01-22���ӡ��人�������������г�*/
select Train.TName
from Train,Station
where Train.SDATE='2020-1-22'
and Train.SStationID=Station.SID
and Station.CityName='�人';
/*5.��ѯ��2020-01-27��;�����人���������г�*/
select Train.TName
from TrainPass,Station,Train
where TrainPass.SID = Station.SID
and Station.CityName='�人'
and TrainPass.TID=Train.TID
and TrainPass.STime >='2020-01-27 00:00:00.000'and TrainPass.STIME<='2020-01-28 00:00:00.000'
/*6.��ѯ��2020-01-22�����人�뿪�����г˿͵����֤�š�������ĳ��С���������*/
select Passenger.PCardID,astation.CityName,atrainpass.STime
from Passenger,Station sstation,Station astation,TrainPass strainpass,TrainPass atrainpass,TakeTrainRecord
where Passenger.PCardID=TakeTrainRecord.PCardID
and sstation.SID=TakeTrainRecord.SStationID
and astation.SID=TakeTrainRecord.AStationID
and strainpass.TID=TakeTrainRecord.TID
and strainpass.SID=TakeTrainRecord.SStationID
and atrainpass.TID=TakeTrainRecord.TID
and atrainpass.SID=TakeTrainRecord.AStationID
and sstation.CityName='�人'
and strainpass.Atime >='2020-01-22 00:00:00.000' and strainpass.ATime<='2020-01-23 00:00:00.000';
/*7.ͳ�ơ�2020-01-22�� ���人�뿪�����г˿�������ĳ��м��ﵽ�������е��人��Ա��*/
select astation.CityName,count( *) as sum
from Passenger,Station sstation,Station astation,
TrainPass strainpass,TrainPass atrainpass,TakeTrainRecord
where Passenger.PCardID=TakeTrainRecord.PCardID
and sstation.SID=TakeTrainRecord.SStationID
and astation.SID=TakeTrainRecord.AStationID
and strainpass.TID=TakeTrainRecord.TID
and strainpass.SID=TakeTrainRecord.SStationID
and atrainpass.TID=TakeTrainRecord.TID
and atrainpass.SID=TakeTrainRecord.AStationID
and sstation.CityName='�人'
and strainpass.Atime >='2020-01-22 00:00:00.000' and strainpass.ATime<='2020-01-23 00:00:00.000'
group by astation.CityName;
/*8.��ѯ2020��1�µ����人��������Ա*/
select Passenger.PName
from TakeTrainRecord,Station,TrainPass,Passenger
where Station.SID=TakeTrainRecord.AStationID
and Passenger.PCardID=TakeTrainRecord.PCardID
and Station.CityName='�人'
and TrainPass.TID=TakeTrainRecord.TID
and TrainPass.SID=TakeTrainRecord.SStationID
and TrainPass.ATime between '2020-01-01' and '2020-01-31';
/*9.��ѯ2020��1�³˳�;���人�������Ա�����֤�ǡ�420����ͷ��*/
select distinct Passenger.PName
from (select  TrainPass.TID,SNo
from TrainPass,Station
where TrainPass.SID=Station.SID
and Station.CityName='�人'
and TrainPass.STime between '2020-1-1'and'2020-1-31')
as passbywh(tid,sno),TakeTrainRecord,Passenger,TrainPass snum,TrainPass anum
where TakeTrainRecord.TID = passbywh.tid
and snum.TID=TakeTrainRecord.TID
and	snum.SID=TakeTrainRecord.SStationID
and anum.TID=TakeTrainRecord.TID
and	anum.SID=TakeTrainRecord.AStationID
and passbywh.sno between snum.SNo and anum.SNo
and Passenger.PCardID=TakeTrainRecord.PCardID
and Passenger.PCardID not like '420%';
/*10.ͳ�ơ�2020-01-22����������G007�����г����¹ڻ����ڻ��ϵ����нӴ��˿�������ÿλ�¹ڻ��ߵ�ͬ������Ա����ͬ�����нӴ���*/
select count(distinct p1.PName) as sum 
from Passenger p1,Passenger p2,TakeTrainRecord t1,TakeTrainRecord t2,DiagnoseRecord,Train
where p2.PCardID=t2.PCardID 
and Train.TID=t2.TID 
and Train.TName='G007'
and Train.SDate='2020-01-22' 
and t2.SStatus=1  
and p1.PCardID=t1.PCardID 
and Train.TID=t1.TID 
and Train.TName='G007' 
and Train.SDate='2020-01-22' 
and t1.SStatus=1 
and p2.PCardID=DiagnoseRecord.PCardID 
and DiagnoseRecord.DStatus=1 
and t1.CarrigeID=t2.CarrigeID
/*11.��ѯһ���г���һ�ڳ�������3�˼����ϳ˿ͱ�ȷ�ϻ����¹ڵ��г������������ڣ������*/
select Train.TName,Train.SDATE,inftrain.CarrigeID
from Train, (select TakeTrainRecord.TID,TakeTrainRecord.CarrigeID
from TakeTrainRecord,DiagnoseRecord
where TakeTrainRecord.PCardID=DiagnoseRecord.PCardID
and DiagnoseRecord.DStatus=1
group by TakeTrainRecord.TID,TakeTrainRecord.CarrigeID
having count(*)>2) 
as inftrain
where Train.TID=inftrain.TID;
/*12.��ѯû�и�Ⱦ�κ��ܱ߳˿͵��¹ڳ˿͵����֤�š��������˳�����*/
select DISTINCT Passenger.PCardID,PName,leavetime=TrainPass.ATime
from Passenger,TakeTrainRecord,TrainPass,DiagnoseRecord,TrainContactor
where Passenger.PCardID=TakeTrainRecord.PCardID
and TakeTrainRecord.SStatus=1
and Passenger.PCardID=DiagnoseRecord.PCardID
and DiagnoseRecord.DStatus=1
and Passenger.PCardID=TrainContactor.PCardID
and TrainContactor.DStatus=3
and TakeTrainRecord.TID=TrainPass.TID
and TakeTrainRecord.SStationID=TrainPass.SID
/*13.��ѯ���� �������������Ϻ������򡰹��ݡ������յ�վ�����г�����Ҫ��where�Ӿ��г�����������ֻ����һ���������ʽ*/
select Train.TName,Station.CityName
from Train,Station
where Station.SID=Train.AStationID
and Station.CityName in('�Ϻ�','����','����')
/*14.��ѯ��2020-01-22���ӡ��人վ��������Ȼ���컻����һ�˳��ĳ˿����֤�ź��׳˳��κţ���������׳˳��κŽ������У�ͬ�������ճ˿����֤����������*/
select fromwh.PName,fromwh.PCardID,fromwh.TID
from TakeTrainRecord,Station,
(select Passenger.PCardID,Passenger.PName,strainpass.TID
from Passenger,Station sstation,Station astation,TrainPass strainpass,TrainPass atrainpass,TakeTrainRecord
where Passenger.PCardID=TakeTrainRecord.PCardID
and sstation.SID=TakeTrainRecord.SStationID
and astation.SID=TakeTrainRecord.AStationID
and strainpass.TID=TakeTrainRecord.TID
and strainpass.SID=TakeTrainRecord.SStationID
and atrainpass.TID=TakeTrainRecord.TID
and atrainpass.SID=TakeTrainRecord.AStationID
and sstation.CityName='�人'
and strainpass.ATime between '2020-1-22' and '2020-1-23') as fromwh
where TakeTrainRecord.SStationID=Station.SID
and station.cityname!='�人'
and TakeTrainRecord.PCardID=fromwh.PCardID
order by fromwh.TID desc,fromwh.PCardID
/*15.��ѯ�����¹ڻ��ߵ����֤�ţ���������2020�����������������г������������ڣ�Ҫ��ʹ�û���δ�������κ��г�ҲҪ�г���*/
select Passenger.PName,Passenger.PCardID,Train.TName,Train.SDate
from Passenger left join TakeTrainRecord on Passenger.PCardID=TakeTrainRecord.PCardID 
left join Train on Train.TID=TakeTrainRecord.TID
and Train.ATime between '2020.1.1' and  '2020.12.31'
inner join DiagnoseRecord on DiagnoseRecord.PCardID=Passenger.PCardID 
and DiagnoseRecord.DStatus=1
/*16.��ѯ���з���������ͬ����ȷ��������ͬ�Ĳ���ͳ����Ϣ���������������ڡ�ȷ�����ںͻ���������������շ������ڽ������е�ǰ�����ٰ���ȷ�����ڽ�������*/
select d1.DDay,d1.FDay ,count (*) as sum 
from DiagnoseRecord d1 where d1.DStatus=1
group by d1.DDay ,d1.FDay
order by d1.DDay desc ,d1.FDay desc