import { FontAwesome } from '@expo/vector-icons';
import React from 'react';
import { Pressable, StyleSheet } from 'react-native';
import { ScrollView } from 'react-native-gesture-handler';
import SequenceComponent from '../components/SequenceComponent';
import TestEvent from '../components/TestEvent';
import { Text, View } from '../components/Themed';
import { useNavigation } from '@react-navigation/core';
import InfoButton from '../components/InfoButton';

export default function ConnectUI() {
  
  const navigation = useNavigation();

  return (
    <View style={styles.container}>
        {/* <Pressable 
            style={styles.infoHead}
            onPress = {() => {
                navigation.navigate("Information");
            }}
        >
            <FontAwesome name="info-circle" size={30} color='grey'/>
        </Pressable> */}
        <InfoButton />
        <ScrollView
            showsVerticalScrollIndicator={false}
            alwaysBounceVertical={false}
            bounces={false}
            bouncesZoom={false}
            overScrollMode="never"
        >
            <View>
                <View style={styles.headerContainer}>
                    <Text style={styles.title}>Test</Text>
                    <FontAwesome style={styles.dropDown} name="chevron-circle-down" size={30} color="grey"/>
                </View>
                <View>
                    <TestEvent />
                    <TestEvent />
                    <TestEvent />
                    <TestEvent />
                    <TestEvent />
                    <TestEvent />
                </View>
            </View>
            <View>
                <View style={styles.headerContainer}>
                    <Text style={styles.title}>Scenarios</Text>
                    <FontAwesome style={styles.dropDown} name="chevron-circle-down" size={30} color="grey"/>
                </View>
                <View>
                    <SequenceComponent />
                    <SequenceComponent />
                    <SequenceComponent />
                    <SequenceComponent />
                    <SequenceComponent />
                    <SequenceComponent />
                    <SequenceComponent />
                </View>
            </View>
        </ScrollView>
        
    </View>
  );
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        justifyContent: 'center',
        margin: 30,
    },
    infoHead: {
        flexDirection: 'row-reverse',
        margin: 20,
    },
    title: {
        fontSize: 50,
        color: 'grey',
        marginRight: 20
    },
    headerContainer:{
        flexDirection: 'row'
    },
    dropDown: {
        marginTop: 10,
    }
})