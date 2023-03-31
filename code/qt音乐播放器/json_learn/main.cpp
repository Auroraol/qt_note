#include <QApplication>
#include <QFile>
#include <QJsonObject>  // { }
#include <QJsonArray>   // [ ]
#include <QJsonDocument>	 // 解析json
#include <QJsonParseError>
#include <QJsonValue>			// int float double bool null { } [ ]

void createJson();
void analysisJson();
void alterJson();
void delJson();

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    createJson();
    analysisJson();
    alterJson();
    delJson();
    return a.exec();
}


void createJson()
{
// 从里到外剥洋葱
// 1. { }
    /*
     *		"interest": {
     *			"basketball": "篮球",
     *			"badminton": "羽毛球"
     *		 },
     */
    // 定义 { } 对象
    QJsonObject interestObj;
    // 插入元素，对应键值对
    interestObj.insert("basketball", "篮球");
    interestObj.insert("badminton", "羽毛球");
// 2. [ ]
    /*
     *		"color": [ "black", "white"],
     */
    // 定义 [ ] 对象
    QJsonArray colorArray;
    // 往数组中添加元素
    colorArray.append("black");
    colorArray.append("white");
// 3. [ { } { } ]
    /*
     *		"like": [
     *			{ "game": "三国", "price": 58.5 },
     *			{ "game": "海岛", "price": 66.65 }
     *		],
     */
    // 定义 { } 对象
    QJsonObject likeObject1;
    likeObject1.insert("game", "三国");
    likeObject1.insert("price", 58.5);
    QJsonObject likeObject2;
    likeObject2.insert("game", "海岛");
    likeObject2.insert("price", 66.65);
    // 定义 [ ] 对象
    QJsonArray likeArray;
    likeArray.append(likeObject1);
    likeArray.append(likeObject2);
// 4. { { } { } }
    /*
     *		"languages": {
     *			"serialOne": { "language": "汉语", "grade": 10 },
     *			"serialTwo": { "language": "英语", "grade": 6 }
     *		},
     */
    // 定义 { } 对象
    QJsonObject language1;
    language1.insert("language", "汉语");
    language1.insert("grade", 10);
    QJsonObject language2;
    language2.insert("language", "英语");
    language2.insert("grade", 6);
    QJsonObject languages;
    // 将{ } 插入 { } 中
    languages.insert("serialOne", language1);
    languages.insert("serialTwo", language2);
// 5. [ [ ], [ ] ]
    /*
     *   "color2": [
     *      [ "black", "white" ],
     *      [ "red", "greed" ]
     *   ]
     */
    // 定义 [ ] 对象
    QJsonArray color;
    // 定义 [ ] 对象
    QJsonArray colorArray1;
    // 往数组中添加元素
    colorArray1.append("black");
    colorArray1.append("white");
    // 定义 [ ] 对象
    QJsonArray colorArray2;
    // 往数组中添加元素
    colorArray2.append("red");
    colorArray2.append("greed");
    color.append(colorArray1);
    color.append(colorArray2);
// 6. 定义根节点 也即是最外层 { }
    QJsonObject rootObject;
// 7. 将上面定义的{ } 与 [ ] 都插入到跟节点{ }中
// 插入元素
    rootObject.insert("name", "老王");
    rootObject.insert("age", 26);
    rootObject.insert("interest", interestObj);
    rootObject.insert("color", colorArray);
    rootObject.insert("like", likeArray);
    rootObject.insert("languages", languages);
    rootObject.insert("vip", true);
    rootObject.insert("address", QJsonValue::Null);
    rootObject.insert("color2", color);
// 8. 实例化QJsonDocument对象
    // 将json对象里的数据转换为字符串
    QJsonDocument doc;
    // 将object设置为本文档的主要对象
    doc.setObject(rootObject);
// 9. Json字符串保存到json文件里
    QFile file("../json_learn/js.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "can't open error!";
        return;
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");		// 设置写入编码是UTF8
    // 写入文件
    stream << doc.toJson();
    file.close();
}


void analysisJson()
{
// 从外向里
    QFile file("../json_learn/js.json");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "can't open error!";
        return;
    }
    // 读取文件的全部内容
    QTextStream stream(&file);
    stream.setCodec("UTF-8");		// 设置读取编码是UTF8
    QString data = stream.readAll();
    file.close();
// 1. 将字符串解析成QJsonDocument对象
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8(), &jsonError); //将json解析为UTF-8编码的json文档
    if (!doc.isNull() && jsonError.error != QJsonParseError::NoError)
    {
        //解析出错判断
        qDebug() <<  "Json格式错误！" << jsonError.errorString(); //返回JSON解析错误时报告的错误信息
        return;
    }
// 2. 获取根对象 { }
    QJsonObject rootObj = doc.object();
// 3. 根据键获取值
    // 根据键获取值
    QJsonValue nameValue = rootObj.value("name");
    qDebug() << "name = " << nameValue.toString();
    QJsonValue ageValue = rootObj.value("age");
    qDebug() << "age = " << ageValue.toInt();
    // 解析 bool类型
    QJsonValue vipValue = rootObj.value("vip");
    qDebug() << "vip = " << vipValue.toBool();
    // 解析 null类型
    QJsonValue addressValue = rootObj.value("address");
    if (addressValue.type() == QJsonValue::Null)
    {
        qDebug() << "address = " << "null";
    }
// 4. 解析对象 { }
    /*解析下图
     *		"interest": {
     *			"basketball": "篮球",
     *			"badminton": "羽毛球"
     *		 },
     */
    QJsonValue interestValue = rootObj.value("interest");
    // 判断是否是object类型
    if (interestValue.type() == QJsonValue::Object)
    {
        // 转换为QJsonObject类型
        QJsonObject interestObj = interestValue.toObject();
        QJsonValue basketballValue = interestObj.value("basketball");
        qDebug() << "basketball = " << basketballValue.toString();
        QJsonValue badmintonValue = interestObj.value("badminton");
        qDebug() << "badminton = " << badmintonValue.toString();
    }
// 5. 解析数组 [ ]
    /*
     *		"color": [ "black", "white"],
     */
    QJsonValue colorValue = rootObj.value("color");
    // 判断是否是Array类型
    if (colorValue.type() == QJsonValue::Array)
    {
        // 转换为QJsonArray类型
        QJsonArray colorArray = colorValue.toArray();
        for (int i = 0; i < colorArray.size(); i++)
        {
            QJsonValue color = colorArray.at(i);
            qDebug() << "color = " << color.toString();
        }
    }
// 6. 解析数组中的对象 [ { } ]
    /*
     *		"like": [
     *			{ "game": "三国", "price": 58.5 },
     *			{ "game": "海岛", "price": 66.65 }
     *		],
     */
    // 根键获取值
    QJsonValue likeValue = rootObj.value("like");
    // 判断类型是否是数组类型
    if (likeValue.type() == QJsonValue::Array)
    {
        // 转换成数组类型
        QJsonArray likeArray = likeValue.toArray();
        // 遍历数组
        for (int i = 0; i < likeArray.count(); i++)
        {
            // 获取数组的第一个元素，类型是QJsonValue
            QJsonValue likeValueChild = likeArray.at(i);
            // 判断是不是对象类型
            if (likeValueChild.type() == QJsonValue::Object)
            {
                // 转换成对象类型
                QJsonObject likeObj = likeValueChild.toObject();
                // 最后通过value函数就可以获取到值了，解析成功！
                QJsonValue gameLikeValue = likeObj.value("game");
                qDebug() << "game = " << gameLikeValue.toString();
                QJsonValue priceLikeValue = likeObj.value("price");
                qDebug() << "price = " << priceLikeValue.toDouble();
            }
        }
    }
// 8. 解析 对象 中 对象 { { } }
    /*
     *		"languages": {
     *			"serialOne": { "language": "汉语", "grade": 10 },
     *			"serialTwo": { "language": "英语", "grade": 6 }
     *		},
     */
    // 根据建获取值
    QJsonValue languagesValue = rootObj.value("languages");
    // 判断是不是对象类型
    if (languagesValue.type() == QJsonValue::Object)
    {
        // 转换成对象类型
        QJsonObject languagesObj = languagesValue.toObject();
        // 根据建获取值
        QJsonValue serialOneValue = languagesObj.value("serialOne");
        // 判断是不是对象类型
        if (serialOneValue.type() == QJsonValue::Object)
        {
            // 转换成对象类型
            QJsonObject serialOneObj = serialOneValue.toObject();
            // 根据建获取值
            QJsonValue languageValue = serialOneObj.value("language");
            // 最后转换成对应类型就解析出来了！
            qDebug() << "language = " << languageValue.toString();
            QJsonValue gradeValue = serialOneObj.value("grade");
            qDebug() << "grade = " << gradeValue.toInt();
        }
        //
        QJsonValue serialTwoValue = languagesObj.value("serialTwo");
        if (serialTwoValue.type() == QJsonValue::Object)
        {
            QJsonObject serialTwoObj = serialTwoValue.toObject();
            QJsonValue languageValue = serialTwoObj.value("language");
            qDebug() << "language = " << languageValue.toString();
            QJsonValue gradeValue = serialTwoObj.value("grade");
            qDebug() << "grade = " << gradeValue.toInt();
        }
    }
// 9. 解析 数组 中 数组 [ [ ] [ ] ]
    /*
     *   "color2": [
     *      [ "black", "white" ],
     *      [ "red", "greed" ]
     *   ]
     */
    // 根键获取值
    QJsonValue colorValue2 = rootObj.value("color2");
    // 判断类型是否是数组类型
    if (colorValue2.type() == QJsonValue::Array)
    {
        // 转换成数组类型
        QJsonArray colorArray = colorValue2.toArray();
        // 遍历数组
        for (int i = 0; i < colorArray.count(); i++)
        {
            // 获取数组的第一个元素，类型是QJsonValue
            QJsonValue colorValueChild = colorArray.at(i);
            // 判断是不是数组类型
            if (colorValueChild.type() == QJsonValue::Array)
            {
                // 转换成数组类型
                QJsonArray colorArr = colorValueChild.toArray();
                for (int i = 0; i < colorArr.size(); i++)
                {
                    QJsonValue color = colorArr.at(i);
                    qDebug() << "color2 = " << color.toString();
                }
            }
        }
    }
}

void alterJson()
{
// 修改就是解析后, 再通过=修改,再覆盖原有的
    /* 修改也就再重写写一遍覆盖掉就行 */
    QFile readFile("../json_learn/js.json");
    if (!readFile.open(QFile::ReadOnly | QFile::Truncate))
    {
        qDebug() << "can't open error!";
        return;
    }
    // 读取文件的全部内容
    QTextStream readStream(&readFile);
    readStream.setCodec("UTF-8");		// 设置读取编码是UTF8
    QString str = readStream.readAll();
    readFile.close();
// 1. 将字符串解析成QJsonDocument对象
    // QJsonParseError类用于在JSON解析期间报告错误。
    QJsonParseError jsonError;
    // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
    // 如果解析成功，返回QJsonDocument对象，否则返回null
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull())
    {
        qDebug() << "Json格式错误！" << jsonError.error;
        return;
    }
// 2. 获取根对象 { }
    QJsonObject rootObj = doc.object();
// 3.修改
    // 修改name, vip, age, address属性
    /*修改下图
     *		"name": "老王"
     *      "vip" : true;
     *
     * 修改后
     *      "name": "老李"
     *      "vip" : false;
     */
    rootObj["name"] = "老李";
    rootObj["vip"] = false;
    // 修改 { } 中的值
    /*修改下图
     *		"interest": {
     *			"basketball": "篮球",
     *			"badminton": "羽毛球"
     *		 },
     *
     *修改后
     *       "interest": {
     *			"basketball": "乒乓球",
     *			"badminton": "足球"
     *		 },
     */
    QJsonValue interestValue = rootObj.value("interest");
    if (interestValue.type() == QJsonValue::Object)
    {
        QJsonObject interestObject = interestValue.toObject();
        interestObject["badminton"] = "乒乓球";
        interestObject["basketball"] = "足球";    //
        // 赋值覆盖原有数组属性
        rootObj["interest"] = interestObject;
    }
    // 修改数组[]中的元素
    /* 修改下图
     *      "color": [ "black", "white"],
     *
     * 修改后
     *      "color": [ "blue", "green"],
     */
    QJsonValue colorValue = rootObj.value("color");
    if (colorValue.type() == QJsonValue::Array)
    {
        QJsonArray colorArray = colorValue.toArray();
        // 修改数组中的值
        colorArray.replace(0, "blue");           //
        colorArray.replace(1, "green");
        // 赋值覆盖原有数组属性
        rootObj["color"] = colorArray;
    }
    // 修改 { { } } 中的值
    QJsonValue languagesValue = rootObj.value("languages");
    if (languagesValue.type() == QJsonValue::Object)
    {
        QJsonObject languagesObj = languagesValue.toObject();
        // 找到内部第一个 { }
        QJsonValue serialOneValue = languagesObj.value("serialOne");
        if (serialOneValue.type() == QJsonValue::Object)
        {
            QJsonObject serialOneObj = serialOneValue.toObject();
            serialOneObj["grade"] = "20";
            languagesObj["serialOne"] = serialOneObj;
        }
        // 找到内部第二个 { }
        QJsonValue serialTwoValue = languagesObj.value("serialTwo");
        if (serialTwoValue.type() == QJsonValue::Object)
        {
            QJsonObject serialTwoObj = serialTwoValue.toObject();
            serialTwoObj["grade"] = "10";
            serialTwoObj["language"] = "粤语";
            languagesObj["serialTwo"] = serialTwoObj;
        }
        rootObj["languages"] = languagesObj;
    }
    // 修改 [ { } ]
    QJsonValue likeValue = rootObj.value("like");
    if (likeValue.type() == QJsonValue::Array)
    {
        QJsonArray likeArray = likeValue.toArray();
        // 根据索引获得对应{ }
        QJsonObject obj1 = likeArray[0].toObject();
        obj1["game"] = "欢乐斗地主";
        obj1["price"] = 88.8;
        QJsonObject obj2 = likeArray[1].toObject();
        obj2["game"] = "欢乐斗牛";
        obj2["price"] = 77.7;
        // 替换覆盖
        likeArray.replace(0, obj1);
        likeArray.replace(1, obj2);
        rootObj["like"] = likeArray;
    }
    // 将object设置为本文档的主要对象
    doc.setObject(rootObj);
    // 重写打开文件，覆盖原有文件，达到删除文件全部内容的效果
    QFile writeFile("../json_learn/js.json");
    if (!writeFile.open(QFile::WriteOnly | QFile::Truncate))
    {
        qDebug() << "can't open error!";
        return;
    }
    // 将修改后的内容写入文件
    QTextStream wirteStream(&writeFile);
    wirteStream.setCodec("UTF-8");		// 设置读取编码是UTF8
    wirteStream << doc.toJson();		// 写入文件
    writeFile.close();					// 关闭文件
}


// 删除Json
void delJson()
{
// 删除就是解析后, 再通过remove()删除,再覆盖原有的
    QFile readFile("../json_learn/js.json");
    if (!readFile.open(QFile::ReadOnly | QFile::Truncate))
    {
        qDebug() << "can't open error!";
        return;
    }
    // 读取文件的全部内容
    QTextStream readStream(&readFile);
    readStream.setCodec("UTF-8");		// 设置读取编码是UTF8
    QString str = readStream.readAll();
    readFile.close();
// 1. 将字符串解析成QJsonDocument对象
    // QJsonParseError类用于在JSON解析期间报告错误。
    QJsonParseError jsonError;
    // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
    // 如果解析成功，返回QJsonDocument对象，否则返回null
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull())
    {
        qDebug() << "Json格式错误！" << jsonError.error;
        return;
    }
// 2. 获取根对象 { }
    QJsonObject rootObj = doc.object();
// 3.删除
    // 删除age
    rootObj.remove("age");
    // 删除 { } 中的值
    QJsonValue interestValue = rootObj.value("interest");
    if (interestValue.type() == QJsonValue::Object)
    {
        QJsonObject interestObject = interestValue.toObject();
        // 删除键为basketball的属性元素
        interestObject.remove("basketball");
        // 重新设置"interest"的值
        rootObj["interest"] = interestObject;
    }
    // 删除数组[]中的元素
    /* 删除下图
     *      "color": [ "blue", "green"],
     *
     * 删除后
     *      "color": [ "blue"],
     */
    QJsonValue colorValue = rootObj.value("color");
    if (colorValue.type() == QJsonValue::Array)
    {
        QJsonArray colorArray = colorValue.toArray();
        // 删除数组中索引为1的值
        colorArray.removeAt(1);
        // 赋值覆盖原有数组属性
        rootObj["color"] = colorArray;
    }
    // 删除 { { } } 中的值
    /*
     *		"languages": {
     *			"serialOne": { "language": "汉语", "grade": 10 },
     *			"serialTwo": { "language": "英语", "grade": 6 }
     *		},
     *
     *删除后
     *      "languages": {
     *			"serialOne": { "language": "汉语", "grade": 10 },
     *		},
     */
    QJsonValue languagesValue = rootObj.value("languages");
    if (languagesValue.type() == QJsonValue::Object)
    {
        QJsonObject languagesObj = languagesValue.toObject();
        // 删除键为serialTwo的对象 { }
        languagesObj.remove("serialTwo");
        rootObj["languages"] = languagesObj;
    }
    // 删除 [ ] 中的 { }
    QJsonValue likeValue = rootObj.value("like");
    if (likeValue.type() == QJsonValue::Array)
    {
        QJsonArray likeArray = likeValue.toArray();
        // 删除索引为1数组中的值
        likeArray.removeAt(1);
        rootObj["like"] = likeArray;
    }
    // 删除 [ ]
    rootObj.remove("color");
    // 删除 { }
    rootObj.remove("interest");
    // 将object设置为本文档的主要对象
    doc.setObject(rootObj);
    // 重写打开文件，覆盖原有文件，达到删除文件全部内容的效果
    QFile writeFile("../json_learn/js.json");
    if (!writeFile.open(QFile::WriteOnly | QFile::Truncate))
    {
        qDebug() << "can't open error!";
        return;
    }
    // 将修改后的内容写入文件
    QTextStream wirteStream(&writeFile);
    wirteStream.setCodec("UTF-8");		// 设置读取编码是UTF8
    wirteStream << doc.toJson();		// 写入文件
    writeFile.close();					// 关闭文件
}



