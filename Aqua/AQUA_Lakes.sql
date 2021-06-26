USE [AQUA_Lakes]
GO

/****** Object:  Table [dbo].[Lakes]    Script Date: 26.6.2021 ã. 18:25:32 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[Lakes](
	[Id] [int] NOT NULL,
	[LakeName] [nvarchar](50) NOT NULL,
	[Mountain] [nvarchar](50) NOT NULL,
	[BeginRiver] [nvarchar](50) NOT NULL,
	[Valley] [nvarchar](50) NOT NULL,
	[Altitude] [int] NOT NULL,
	[Area] [float] NOT NULL,
	[Volume] [float] NULL,
	[MaxDepth] [float] NULL,
 CONSTRAINT [PK_Lakes] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO


