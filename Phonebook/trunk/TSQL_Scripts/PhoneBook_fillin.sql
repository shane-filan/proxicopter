
DECLARE @rev_nmbr int

SET @rev_nmbr = '0'

INSERT INTO [phonebook].[dbo].[cities]
           ([id]
           ,[rev_nmb]
           ,[code]
           ,[name]
           ,[area])
     VALUES
           ('0'
           ,@rev_nmbr
           ,N'052'
           ,N'�����'
           ,N'�����')

INSERT INTO [phonebook].[dbo].[cities]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,[name]
           ,[area])
     VALUES
           ('1'
           ,@rev_nmbr
           ,N'056'
           ,N'������'
           ,N'������')
           
INSERT INTO [phonebook].[dbo].[cities]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,[name]
           ,[area])
     VALUES
           ('2'
           ,@rev_nmbr
           ,N'02'
           ,N'�����'
           ,N'�����')

INSERT INTO [phonebook].[dbo].[cities]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,[name]
           ,[area])
     VALUES
           ('3'
           ,@rev_nmbr
           ,N'032'
           ,N'�������'
           ,N'�������')                                  
           
INSERT INTO [phonebook].[dbo].[phones]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,phone_type)
     VALUES
           ('0'
           ,@rev_nmbr
           ,'11'
           ,N'�������')    
           
INSERT INTO [phonebook].[dbo].[phones]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,phone_type)
     VALUES
           ('1'
           ,@rev_nmbr
           ,'22'
           ,N'����')
                                               
INSERT INTO [phonebook].[dbo].[phones]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,phone_type)
     VALUES
           ('2'
           ,@rev_nmbr
           ,'33'
           ,N'�����')
           
INSERT INTO [phonebook].[dbo].[subscribers]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,[first_name]
           ,[second_name]
           ,[third_name]
           ,[ident_nmb]
           ,[city_id]
           ,[city_addr])
     VALUES
           ('0'
           ,@rev_nmbr          
           ,'989'
           ,N'�������' 
           ,N'������'
           ,N'��������' 
           ,'8606070000'
           ,'2'
           ,'������ 9')

INSERT INTO [phonebook].[dbo].[subscribers]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,[first_name]
           ,[second_name]
           ,[third_name]
           ,[ident_nmb]
           ,[city_id]
           ,[city_addr])
     VALUES
           ('1'
           ,@rev_nmbr          
           ,'1203'
           ,N'����' 
           ,N'��������'
           ,N'��������' 
           ,'8605280000'
           ,'0'
           ,'������� 3, ��. 32')

           
           
INSERT INTO [phonebook].[dbo].[subscriber_phone_numbers]
           ([id]
           ,[rev_nmb]           
           ,[subscriber_id]
           ,[phone_id]
           ,[phone_number])
     VALUES
           ('0'
           ,@rev_nmbr           
           ,'0'
           ,'2'
           ,N'785209')

INSERT INTO [phonebook].[dbo].[subscriber_phone_numbers]
           ([id]
           ,[rev_nmb]           
           ,[subscriber_id]
           ,[phone_id]
           ,[phone_number])
     VALUES
           ('1'
           ,@rev_nmbr
           ,'1'
           ,'0'
           ,N'0878123456')
                      
GO


