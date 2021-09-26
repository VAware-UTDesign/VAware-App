import { FontAwesome } from '@expo/vector-icons';
import React from 'react'
import { Text, View, StyleSheet, ScrollView } from 'react-native'
import InfoButton from '../components/InfoButton';
import SequenceComponent from '../components/SequenceComponent'
import TestEvent from '../components/TestEvent';

export default function SequenceScreen(){
    return (
        <View 
            style={styles.container}
        >
            <InfoButton />
            <Text style={styles.headerText}>Series</Text>
            <ScrollView 
                showsVerticalScrollIndicator={false}
                alwaysBounceVertical={false}
                bounces={false}
                bouncesZoom={false}
                overScrollMode="never"
            >
                <TestEvent />
                <TestEvent />
                <TestEvent />
                <TestEvent />
                <TestEvent />
                <TestEvent />
                <TestEvent />
            </ScrollView>
        </View>
    )
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        justifyContent: "center",
        margin: 30,
    },
    headerContainer: {
        //width: 330,
        flexDirection: 'row-reverse',
        margin: 20,
        // backgroundColor: 'red',
    },
    headerText: {
        // alignItems: 'flex-start',
        // fontSize: 30,
        // maxWidth: 350,
        fontSize: 50,
        color: 'grey',
        marginRight: 20
        // backgroundColor: 'red'
    },
    scroll: {
        // backgroundColor: 'red'
    }
});